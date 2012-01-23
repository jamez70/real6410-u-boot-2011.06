/*
 * (C) Copyright 2008 - 2009
 * Windriver, <www.windriver.com>
 * Tom Rix <Tom.Rix@windriver.com>
 *
 * Copyright (c) 2011 Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Part of the rx_handler were copied from the Android project.
 * Specifically rx command parsing in the  usb_rx_data_complete
 * function of the file bootable/bootloader/legacy/usbloader/usbloader.c
 *
 * The logical naming of flash comes from the Android project
 * Thse structures and functions that look like fastboot_flash_*
 * They come from bootable/bootloader/legacy/libboot/flash.c
 *
 * This is their Copyright:
 *
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <common.h>
#include <fastboot.h>
#include <usb/fastboot.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <nand.h>
#include "g_fastboot.h"

/* The 64 defined bytes plus \0 */
#define RESPONSE_LEN	(64 + 1)

#define MAX_PTN 16

static fastboot_ptentry ptable[MAX_PTN];
unsigned int pcount = 0;
int static_pcount = -1;

int quitThis = 0;
static unsigned int download_size;
static unsigned int download_bytes;
static unsigned int download_bytes_unpadded;

static struct cmd_fastboot_interface interface = {
	.product_name          = CONFIG_FASTBOOT_PRODUCT_NAME,
	.serial_no             = CONFIG_FASTBOOT_SERIAL,
	.nand_block_size       = FASTBOOT_NAND_BLOCK_SIZE,
	.transfer_buffer       = CONFIG_FASTBOOT_TRANSFER_BUFFER,
	.transfer_buffer_size  = CONFIG_FASTBOOT_TRANSFER_BUFFER_SIZE,
};

extern int setenv(char *varname, char *varvalue);
extern int do_nand(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

void fastboot_flash_add_ptn(fastboot_ptentry *ptn)
{
	if (pcount < MAX_PTN) {
		memcpy(ptable + pcount, ptn, sizeof(fastboot_ptentry));
		pcount++;
	}
}



void fastboot_flash_dump_ptn(void)
{
	unsigned int n;
	for (n = 0; n < pcount; n++) {
		fastboot_ptentry *ptn = ptable + n;
		printf("ptn %d name='%s' start=%d len=%d\n",
			n, ptn->name, ptn->start, ptn->length);
	}
}


fastboot_ptentry *fastboot_flash_find_ptn(const char *name)
{
	unsigned int n;
	for (n = 0; n < pcount; n++) {
		/* Make sure a substring is not accepted */
		if (strlen(name) == strlen(ptable[n].name)) {
			if (0 == strcmp(ptable[n].name, name))
			{
				return ptable + n;
			}
		}
	}
	return 0;
}

fastboot_ptentry *fastboot_flash_get_ptn(unsigned int n)
{
	if (n < pcount)
		return ptable + n;
	else
		return 0;
}

unsigned int fastboot_flash_get_ptn_count(void)
{
	return pcount;
}


static void save_block_values(struct fastboot_ptentry *ptn,
			      unsigned int offset,
			      unsigned int size)
{
	struct fastboot_ptentry *env_ptn;

	char var[64], val[32];
	char start[32], length[32];
	char ecc_type[32];

	char *lock[5]    = { "nand", "lock",   NULL, NULL, NULL, };
	char *unlock[5]  = { "nand", "unlock", NULL, NULL, NULL, };
	char *ecc[4]     = { "nand", "ecc",    NULL, NULL, };

	lock[2] = unlock[2] = start;
	lock[3] = unlock[3] = length;

	printf("saving it..\n");

	if (size == 0) {
		/* The error case, where the variables are being unset */

		sprintf(var, "%s_nand_offset", ptn->name);
		val[0]=0;
		setenv(var,val);

		sprintf(var, "%s_nand_size", ptn->name);
		val[0]=0;
		setenv(var,val);
	} else {
		/* Normal case */

		sprintf(var, "%s_nand_offset", ptn->name);
		sprintf(val, "0x%x", offset);

		printf("setenv %s %s\n", var,val);

		setenv(var,val);

		sprintf(var, "%s_nand_size", ptn->name);

		sprintf(val, "0x%x", size);

		printf("setenv %s %s\n", var,val);

		setenv(var,val);
	}


	/* Warning :
	   The environment is assumed to be in a partition named 'enviroment'.
	   It is very possible that your board stores the enviroment
	   someplace else. */
	env_ptn = fastboot_flash_find_ptn("environment");

	if (env_ptn) {
		/* Some flashing requires the nand's ecc to be set */
		ecc[2] = ecc_type;
		if ((env_ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_HW_ECC) &&
		    (env_ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_SW_ECC)) {
			/* Both can not be true */
			printf("Warning can not do hw and sw ecc for \
				partition '%s'\n", ptn->name);
			printf("Ignoring these flags\n");

		}
#if 0
		else if (env_ptn->flags &
			    FASTBOOT_PTENTRY_FLAGS_WRITE_HW_ECC) {
			sprintf(ecc_type, "hw");
			do_nand(NULL, 0, 3, ecc);
		} else if (env_ptn->flags &
			    FASTBOOT_PTENTRY_FLAGS_WRITE_SW_ECC) {
			sprintf(ecc_type, "sw");
			do_nand(NULL, 0, 3, ecc);
		}
#endif
		sprintf(start, "0x%x", env_ptn->start);
		sprintf(length, "0x%x", env_ptn->length);

		/* This could be a problem is there is an outstanding lock */
//		do_nand(NULL, 0, 4, unlock);
	}

	saveenv();

//	if (env_ptn)
//		do_nand(NULL, 0, 4, lock);
}

static int write_to_ptn(struct fastboot_ptentry *ptn)
{
	int ret = 1;
	char start[32], length[32];
	char wstart[32], wlength[32], addr[32];
	char write_type[32];
	int repeat, repeat_max;

	char *lock[5]   = { "nand", "lock",   NULL, NULL, NULL, };
	char *unlock[5] = { "nand", "unlock", NULL, NULL, NULL,	};
	char *write[6]  = { "nand", "write",  NULL, NULL, NULL, NULL, };
	char *erase[5]  = { "nand", "erase",  NULL, NULL, NULL, };

	lock[2] = unlock[2] = erase[2] = start;
	lock[3] = unlock[3] = erase[3] = length;

	write[1] = write_type;
	write[2] = addr;
	write[3] = wstart;
	write[4] = wlength;

	printf("flashing '%s'\n", ptn->name);

	/* Which flavor of write to use */
	if (ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_I)
		sprintf(write_type, "write.i");
#ifdef CONFIG_CMD_NAND_YAFFS 
	else if (ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_YAFFS)
		sprintf(write_type, "write.yaffs");
#endif
	else
		sprintf(write_type, "write");

//	set_ptn_ecc(ptn);

	/* Some flashing requires writing the same data in multiple,
	   consecutive flash partitions */
	repeat_max = 1;
#if 0
	if (ptn->flags & FASTBOOT_PTENTRY_FLAGS_REPEAT_MASK) {
		if (ptn->flags &
		    FASTBOOT_PTENTRY_FLAGS_WRITE_CONTIGUOUS_BLOCK) {
			printf("Warning can not do both 'contiguous block' and 'repeat' writes for for partition '%s'\n", ptn->name);
			printf("Ignoring repeat flag\n");
		} else {
			repeat_max = ptn->flags &
				FASTBOOT_PTENTRY_FLAGS_REPEAT_MASK;
		}
	}
#endif
	/* Unlock the whole partition instead of trying to
	   manage special cases */
	sprintf(length, "0x%x", ptn->length * repeat_max);

	for (repeat = 0; repeat < repeat_max; repeat++) {
		sprintf(start, "0x%x", ptn->start + (repeat * ptn->length));

//		do_nand(NULL, 0, 4, unlock);
		do_nand(NULL, 0, 4, erase);

		if ((ptn->flags &
		     FASTBOOT_PTENTRY_FLAGS_WRITE_NEXT_GOOD_BLOCK) &&
		    (ptn->flags &
		     FASTBOOT_PTENTRY_FLAGS_WRITE_CONTIGUOUS_BLOCK)) {
			/* Both can not be true */
			printf("Warning can not do 'next good block' and \
				'contiguous block' for partition '%s'\n",
				ptn->name);
			printf("Ignoring these flags\n");
		} else if (ptn->flags &
			   FASTBOOT_PTENTRY_FLAGS_WRITE_NEXT_GOOD_BLOCK) {
			/* Keep writing until you get a good block
			   transfer_buffer should already be aligned */
			if (interface.nand_block_size) {
				unsigned int blocks = download_bytes /
					interface.nand_block_size;
				unsigned int i = 0;
				unsigned int offset = 0;

				sprintf(wlength, "0x%x",
					interface.nand_block_size);
				while (i < blocks) {
					/* Check for overflow */
					if (offset >= ptn->length)
						break;

					/* download's address only advance
					   if last write was successful */
					sprintf(addr, "0x%x",
						(unsigned int)(interface.transfer_buffer +
						(i * interface.nand_block_size)));

					/* nand's address always advances */
					sprintf(wstart, "0x%x",
						ptn->start + (repeat * ptn->length) + offset);

					ret = do_nand(NULL, 0, 5, write);
					if (ret)
						break;
					else
						i++;

					/* Go to next nand block */
					offset += interface.nand_block_size;
				}
			} else {
				printf("Warning nand block size can not be 0 \
					when using 'next good block' for \
					partition '%s'\n", ptn->name);
				printf("Ignoring write request\n");
			}
		} else if (ptn->flags &
			 FASTBOOT_PTENTRY_FLAGS_WRITE_CONTIGUOUS_BLOCK) {
			/* Keep writing until you get a good block
			   transfer_buffer should already be aligned */
			if (interface.nand_block_size) {
				if (0 == nand_curr_device) {
					nand_info_t *nand;
					unsigned long off;
					unsigned int ok_start;

					nand = &nand_info[nand_curr_device];

					printf("\nDevice %d bad blocks:\n",
					       nand_curr_device);

					/* Initialize the ok_start to the
					   start of the partition
					   Then try to find a block large
					   enough for the download */
					ok_start = ptn->start;

					/* It is assumed that the start and
					   length are multiples of block size */
					for (off = ptn->start;
					     off < ptn->start + ptn->length;
					     off += nand->erasesize) {
						if (nand_block_isbad(nand, off)) {
							/* Reset the ok_start
							   to the next block */
							ok_start = off +
								nand->erasesize;
						}

						/* Check if we have enough
						   blocks */
						if ((ok_start - off) >=
						    download_bytes)
							break;
					}

					/* Check if there is enough space */
					if (ok_start + download_bytes <=
					    ptn->start + ptn->length) {
						sprintf(addr,    "0x%x", (unsigned int)interface.transfer_buffer);
						sprintf(wstart,  "0x%x", ok_start);
						sprintf(wlength, "0x%x", download_bytes);

						ret = do_nand(NULL, 0, 5, write);

						/* Save the results into an
						   environment variable on the
						   format
						   ptn_name + 'offset'
						   ptn_name + 'size'  */
						if (ret) {
							/* failed */
							save_block_values(ptn, 0, 0);
						} else {
							/* success */
							save_block_values(ptn, ok_start, download_bytes);
						}
					} else {
						printf("Error could not find enough contiguous space in partition '%s' \n", ptn->name);
						printf("Ignoring write request\n");
					}
				} else {
					/* TBD : Generalize flash handling */
					printf("Error only handling 1 NAND per board");
					printf("Ignoring write request\n");
				}
			} else {
				printf("Warning nand block size can not be 0 \
					when using 'continuous block' for \
					partition '%s'\n", ptn->name);
				printf("Ignoring write request\n");
			}
		} else {
			/* Normal case */
			sprintf(addr,    "0x%x", (unsigned int)interface.transfer_buffer);
			sprintf(wstart,  "0x%x", ptn->start +
				(repeat * ptn->length));
			sprintf(wlength, "0x%x", download_bytes);
#ifdef CONFIG_CMD_NAND_YAFFS
			if (ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_YAFFS)
				sprintf(wlength, "0x%x",
					download_bytes_unpadded);
#endif

			ret = do_nand(NULL, 0, 5, write);

			if (0 == repeat) {
				if (ret) /* failed */
					save_block_values(ptn, 0, 0);
				else     /* success */
					save_block_values(ptn, ptn->start,
							  download_bytes);
			}
		}

//		do_nand(NULL, 0, 4, lock);

		if (ret)
			break;
	}

	return ret;
}



static int fastboot_tx_write_str(const char *buffer)
{
	return fastboot_tx_write(buffer, strlen(buffer));
}

static void compl_do_reset(struct usb_ep *ep, struct usb_request *req)
{
	do_reset(NULL, 0, 0, NULL);
}

static void cb_reboot(struct usb_ep *ep, struct usb_request *req)
{
	printf("reboot callback handler\n");
	req_in->complete = compl_do_reset;
	fastboot_tx_write_str("OKAY");
}

static int strcmp_l1(const char *s1, const char *s2)
{
	return strncmp(s1, s2, strlen(s1));
}

static void cb_getvar(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];
	const char *s;

	strcpy(response, "OKAY");
	strsep(&cmd, ":");
	if (!cmd) {
		fastboot_tx_write_str("FAILmissing var");
		return;
	}

	if (!strcmp_l1("version", cmd)) {
		strncat(response, FASTBOOT_VERSION, sizeof(response));

	} else if (!strcmp_l1("downloadsize", cmd)) {
		char str_num[12];

		sprintf(str_num, "%08x", interface.transfer_buffer_size);
		strncat(response, str_num, sizeof(response));

	} else if (!strcmp_l1("product", cmd)) {

		s = fb_find_usb_string(FB_STR_PRODUCT_IDX);
		if (s)
			strncat(response, s, sizeof(response));
		else
			strcpy(response, "FAILValue not set");

	} else if (!strcmp_l1("serialno", cmd)) {

		s = fb_find_usb_string(FB_STR_SERIAL_IDX);
		if (s)
			strncat(response, s, sizeof(response));
		else
			strcpy(response, "FAILValue not set");

	} else if (!strcmp_l1("cpurev", cmd)) {

		s = fb_find_usb_string(FB_STR_PROC_REV_IDX);
		if (s)
			strncat(response, s, sizeof(response));
		else
			strcpy(response, "FAILValue not set");
	} else if (!strcmp_l1("secure", cmd)) {

		s = fb_find_usb_string(FB_STR_PROC_TYPE_IDX);
		if (s)
			strncat(response, s, sizeof(response));
		else
			strcpy(response, "FAILValue not set");
	} else {
		strcpy(response, "FAILVariable not implemented");
	}
	fastboot_tx_write_str(response);
}

static unsigned int rx_bytes_expected(void)
{
	int rx_remain = download_size - download_bytes;
	if (rx_remain < 0)
		return 0;
	if (rx_remain > EP_BUFFER_SIZE)
		return EP_BUFFER_SIZE;
	return rx_remain;
}

#define BYTES_PER_DOT	32768
static void rx_handler_dl_image(struct usb_ep *ep, struct usb_request *req)
{
	char response[RESPONSE_LEN];
	unsigned int transfer_size = download_size - download_bytes;
	const unsigned char *buffer = req->buf;
	unsigned int buffer_size = req->actual;

	if (req->status != 0) {
		printf("Bad status: %d\n", req->status);
		return;
	}

	if (buffer_size < transfer_size)
		transfer_size = buffer_size;

	memcpy(interface.transfer_buffer + download_bytes,
			buffer, transfer_size);

	download_bytes += transfer_size;

	/* Check if transfer is done */
	if (download_bytes >= download_size) {
		/*
		 * Reset global transfer variable, keep download_bytes because
		 * it will be used in the next possible flashing command
		 */
		download_size = 0;
		req->complete = rx_handler_command;
		req->length = EP_BUFFER_SIZE;
		download_bytes_unpadded = download_bytes;
		sprintf(response, "OKAY");
		fastboot_tx_write_str(response);

		printf("\ndownloading of %d bytes finished\n",
				download_bytes);
	} else
		req->length = rx_bytes_expected();

	if (download_bytes && !(download_bytes % BYTES_PER_DOT)) {
		printf(".");
		if (!(download_bytes % (74 * BYTES_PER_DOT)))
				printf("\n");

	}
	req->actual = 0;
	usb_ep_queue(ep, req, 0);
}

static void cb_download(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];

	strsep(&cmd, ":");
	download_size = simple_strtoul(cmd, NULL, 16);
	download_bytes = 0;

	printf("Starting download of %d bytes\n",
			download_size);

	if (0 == download_size) {
		sprintf(response, "FAILdata invalid size");
	} else if (download_size >
			interface.transfer_buffer_size) {
		download_size = 0;
		sprintf(response, "FAILdata too large");
	} else {
		sprintf(response, "DATA%08x", download_size);
		req->complete = rx_handler_dl_image;
		req->length = rx_bytes_expected();
	}
	fastboot_tx_write_str(response);
}

static void cb_erase(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];

	struct fastboot_ptentry *ptn;

	strsep(&cmd, ":");
	ptn = fastboot_flash_find_ptn(cmd);
	if (ptn == 0)
	{
		sprintf(response, "FAILpartition does not exist");
	}
	else
	{
		char start[32], length[32];
		int status, repeat, repeat_max;

		printf("erasing '%s'\n", ptn->name);

		char *lock[5]   = { "nand", "lock",   NULL, NULL, NULL, };
		char *unlock[5] = { "nand", "unlock", NULL, NULL, NULL,	};
		char *erase[5]  = { "nand", "erase",  NULL, NULL, NULL, };

		lock[2] = unlock[2] = erase[2] = start;
		lock[3] = unlock[3] = erase[3] = length;

		repeat_max = 1;
#if 0
		if (ptn->flags & FASTBOOT_PTENTRY_FLAGS_REPEAT_MASK)
			repeat_max = ptn->flags & FASTBOOT_PTENTRY_FLAGS_REPEAT_MASK;
#endif
		sprintf(length, "0x%x", ptn->length);
		for (repeat = 0; repeat < repeat_max;
			repeat++)
		{
			sprintf(start, "0x%x",
				ptn->start +
				(repeat * ptn->length));
			printf("nand erase %s %s\n",erase[2],erase[3]);
//			do_nand(NULL, 0, 4, unlock);
			status = do_nand(NULL, 0, 4, erase);
//			do_nand(NULL, 0, 4, lock);

			if (status)
				break;
		}

		if (status)
		{
			sprintf(response,
					"FAILfailed to erase partition");
		}
		else
		{
			printf("partition '%s' erased\n", ptn->name);
			sprintf(response, "OKAY");
		}

	}
	fastboot_tx_write_str(response);
}

static void cb_flash(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];

			struct fastboot_ptentry *ptn;

	strsep(&cmd, ":");
	if (download_bytes) {
		struct fastboot_ptentry *ptn;

		ptn = fastboot_flash_find_ptn(cmd);
		if (ptn == 0) {
			sprintf(response, "FAILpartition does not exist");
		} else if ((download_bytes > ptn->length) &&
				!(ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_ENV)) {
			sprintf(response, "FAILimage too large for partition");
			/* TODO : Improve check for yaffs write */
		} else {
			/* Check if this is not really a flash write
				but rather a saveenv */
			if (ptn->flags & FASTBOOT_PTENTRY_FLAGS_WRITE_ENV) {
				/* Since the response can only be 64 bytes,
					there is no point in having a large error message. */
				char err_string[32];
#if 0
				if (saveenv_to_ptn(ptn, &err_string[0])) {
					printf("savenv '%s' failed : %s\n", ptn->name, err_string);
					sprintf(response, "FAIL%s", err_string);
				} else {
					printf("partition '%s' saveenv-ed\n", ptn->name);
					sprintf(response, "OKAY");
				}
#endif
			} else {
				/* Normal case */
				if (write_to_ptn(ptn)) {
					printf("flashing '%s' failed\n", ptn->name);
					sprintf(response, "FAILfailed to flash partition");
				} else {
					printf("partition '%s' flashed\n", ptn->name);
					sprintf(response, "OKAY");
				}
			}
		}
	} else {
		sprintf(response, "FAILno image downloaded");
	}
	fastboot_tx_write_str(response);
}

static char boot_addr_start[32];
static char *bootm_args[] = { "bootm", boot_addr_start, NULL };

static void do_bootm_on_complete(struct usb_ep *ep, struct usb_request *req)
{
	req->complete = NULL;
	fastboot_shutdown();
	printf("Booting kernel..\n");

	do_bootm(NULL, 0, 2, bootm_args);

	/* This only happens if image is somehow faulty so we start over */
	do_reset(NULL, 0, 0, NULL);
}

static void cb_boot(struct usb_ep *ep, struct usb_request *req)
{
	sprintf(boot_addr_start, "0x%p", interface.transfer_buffer);

	req_in->complete = do_bootm_on_complete;
	fastboot_tx_write_str("OKAY");
	return;
}

static void cb_cont(struct usb_ep *ep, struct usb_request *req)
{
	quitThis=1;
	fastboot_tx_write_str("OKAY");
	return;
}

struct cmd_dispatch_info {
	char *cmd;
	void (*cb)(struct usb_ep *ep, struct usb_request *req);
};

static struct cmd_dispatch_info cmd_dispatch_info[] = {
	{
		.cmd = "reboot",
		.cb = cb_reboot,
	}, {
		.cmd = "getvar:",
		.cb = cb_getvar,
	}, {
		.cmd = "download:",
		.cb = cb_download,
	}, {
		.cmd = "erase:",
		.cb = cb_erase,
	}, {
		.cmd = "flash:",
		.cb = cb_flash,
	}, {
		.cmd = "continue",
		.cb = cb_cont,
	}, {
		.cmd = "boot",
		.cb = cb_boot,
	},
};

void rx_handler_command(struct usb_ep *ep, struct usb_request *req)
{
	char response[RESPONSE_LEN];
	char *cmdbuf = req->buf;
	void (*func_cb)(struct usb_ep *ep, struct usb_request *req) = NULL;
	int i;

	if (req->actual < req->length)
	{
		cmdbuf[req->actual]=0;
	}
	printf("rx_handler_command '%s' actual %d\n",cmdbuf,req->actual);
	sprintf(response, "FAIL");
	for (i = 0; i < ARRAY_SIZE(cmd_dispatch_info); i++) {
		if (!strcmp_l1(cmd_dispatch_info[i].cmd, cmdbuf)) {
			func_cb = cmd_dispatch_info[i].cb;
			break;
		}
	}
	if (!func_cb)
		fastboot_tx_write_str("FAILunknown command ");
	else
		func_cb(ep, req);

	if (req->status == 0) {
		*cmdbuf = '\0';
		req->actual = 0;
		usb_ep_queue(ep, req, 0);
	}
}
