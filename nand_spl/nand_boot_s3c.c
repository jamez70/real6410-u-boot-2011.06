/*
 * (C) Copyright 2010
 * Darius Augulis, <augulis.darius@gmail.com>
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
 */

#include <config.h>
#include <version.h>
#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/arch/s3c6400.h>

static void disable_ce(void)
{
	int val = readl(NFCONT);
	writel(val | (1 << 1), NFCONT);
}

static void enable_ce(void)
{
	int val = readl(NFCONT);
	writel(val & ~(1 << 1), NFCONT);
}

static int nand_is_ready(void)
{
	return readl(NFSTAT) & 0x01;
}

static void nand_read_page(unsigned int block, unsigned int page, uchar *buf)
{
	int i;

	writel(NAND_CMD_READ0, NFCMMD);

	writel(0, NFADDR);
	writel(0, NFADDR);
	writel((page & 0x3f) | ((block << 6) & 0xC0), NFADDR);
	writel((block >> 2) & 0xff, NFADDR);
	writel((block >> 16) & 0xff, NFADDR);

	writel(NAND_CMD_READSTART, NFCMMD);

	while(!nand_is_ready());

	for(i = 0; i < CONFIG_SYS_NAND_PAGE_SIZE; i++)
		buf[i] = readb(NFDATA);
}

static int nand_load(unsigned int offs, unsigned int uboot_size, uchar *dst)
{
	unsigned int block, lastblock, page;

	/* offs has to be aligned to a page address! */
	block = offs / CONFIG_SYS_NAND_BLOCK_SIZE;
	lastblock = (offs + uboot_size - 1) / CONFIG_SYS_NAND_BLOCK_SIZE;
	page = (offs % CONFIG_SYS_NAND_BLOCK_SIZE) / CONFIG_SYS_NAND_PAGE_SIZE;

	while (block <= lastblock) {
		while (page < CONFIG_SYS_NAND_PAGE_COUNT) {
			nand_read_page(block, page, dst);
			dst += CONFIG_SYS_NAND_PAGE_SIZE;
			page++;
		}
		page = 0;
		block++;
	}

	return;
}

#if defined(CONFIG_ARM) && !defined(CONFIG_SYS_ARM_WITHOUT_RELOC)
void board_init_f (ulong bootflag)
{
	relocate_code (CONFIG_SYS_TEXT_BASE - TOTAL_MALLOC_LEN, NULL,
		       CONFIG_SYS_TEXT_BASE);
}
#endif

static void nand_init_hw(void)
{
	int val;

	/* Set timing */
	val = readl(NFCONF);
	writel(val | 0x7770, NFCONF);

	/* Enable NFC, release both CE's */
	val = readl(NFCONT);
	writel(val | 0x07, NFCONT);
}

/*
 * The main entry for NAND booting. It's necessary that SDRAM is already
 * configured and available since this code loads the main U-Boot image
 * from NAND into SDRAM and starts it from there.
 */
void nand_boot(void)
{
	__attribute__((noreturn)) void (*uboot)(void);

	/* Init nand controller */
	nand_init_hw();

	enable_ce();

	/* Load U-Boot image from NAND into RAM */
	nand_load(CONFIG_SYS_NAND_U_BOOT_OFFS,
		CONFIG_SYS_NAND_U_BOOT_SIZE,
		(uchar *)CONFIG_SYS_NAND_U_BOOT_DST);

	disable_ce();

	uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
	(*uboot)();
}
