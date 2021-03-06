/*
 * (C) Copyright 2010
 * Darius Augulis <augulis.darius@gmail.com>
 *
 * (C) Copyright 2008
 * Guennadi Liakhovetki, DENX Software Engineering, <lg@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* High Level Configuration Options */
#define CONFIG_S3C6410			1
#define CONFIG_S3C64XX			1
#define CONFIG_MINI6410			1

#define CONFIG_SYS_AUTOLOAD
#define CONFIG_SYS_NO_FLASH		1
#define CONFIG_NAND_U_BOOT		1

#define CONFIG_PERIPORT_REMAP
#define CONFIG_PERIPORT_BASE		0x70000000
#define CONFIG_PERIPORT_SIZE		0x13

/* Relocation and internal SRAM options */
#define CONFIG_SYS_IRAM_BASE		0x0C000000	/* Internal SRAM base address */
#define CONFIG_SYS_IRAM_SIZE		0x2000		/* 8 KB of internal SRAM memory */
#define CONFIG_SYS_IRAM_END		(CONFIG_SYS_IRAM_BASE + CONFIG_SYS_IRAM_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_IRAM_END - GENERATED_GBL_DATA_SIZE)

/* SDRAM options */
#define CONFIG_SYS_SDRAM_BASE		0x50000000
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		CONFIG_SYS_TEXT_BASE	/* 126MiB in DRAM */
#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_SDRAM_BASE	/* default load address	*/
#define CONFIG_LOADADDR 			0x50000000

#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 1024 * 1024 * 2)
#define CONFIG_SYS_UBOOT_BASE		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_UBOOT_SIZE		(1024 * 1024 * 2)

#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define PHYS_SDRAM_1_SIZE		0x10000000		/* 128 MB */

/* Environment options */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_SIZE			0x40000
#define CONFIG_ENV_OFFSET		0xc0000
#define CONFIG_ENV_IS_IN_NAND

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"\x1b[1;32mREAL6410 \x1b[1;33m# \x1b[0m"
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		384
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_IDENT_STRING		" for MINI6410"

#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_CLK_FREQ		12000000
#define MACH_TYPE			1626
#define CONFIG_BOOTDELAY		5

#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG    1

#define CONFIG_ZIMAGE_BOOT
#define CONFIG_IMAGE_BOOT

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_ZERO_BOOTDELAY_CHECK

#define BOARD_LATE_INIT

#define CONFIG_CLK_800_133_66
#define CONFIG_SYNC_MODE

/* Network */
#define CONFIG_NET_MULTI		1
#define CONFIG_DRIVER_DM9000		1
#define CONFIG_DM9000_NO_SROM		1
#define CONFIG_DM9000_BASE		0x18000000
#define DM9000_IO			CONFIG_DM9000_BASE
#define DM9000_DATA			(CONFIG_DM9000_BASE+4)
#define CONFIG_ETHADDR			00:01:02:03:04:05
#define CONFIG_IPADDR			192.168.0.91
#define CONFIG_SERVERIP			192.168.0.2
#define CONFIG_GATEWAYIP		192.168.0.1
#define CONFIG_NETMASK			255.255.255.0

/* serial console configuration */
#define CONFIG_SERIAL1			1
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_BOOTCOMMAND	"nand read ${loadaddr} kernel;bootm ${loadaddr}"
#define CONFIG_BOOTARGS    	"setenv bootargs noinitrd mem=224M console=ttySAC0,115200 init=/init root=/dev/mtdblock4 rootfstype=yaffs2"

/* Command definition */
#include <config_cmd_default.h>
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_PING
#define CONFIG_CMD_NAND
#define CONFIG_CMD_UNZIP
#define CONFIG_CMD_MTDPARTS
//#define CONFIG_CMD_FLASH
#define CONFIG_CMD_FAT
#define CONFIG_SUPPORT_VFAT
#define CONFIG_JFFS2_NAND
#define CONFIG_CMD_EDITENV
#define CONFIG_CMD_SOURCE
#define CONFIG_CMD_NAND_YAFFS
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_SAVEENV

/* NAND configuration */
#define CONFIG_MTD_DEBUG
#define CONFIG_MTD_DEBUG_VERBOSE 1

/* NAND chip page size		*/
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
/* NAND chip block size		*/
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128 * 1024)
/* NAND chip page per block count  */
#define CONFIG_SYS_NAND_PAGE_COUNT	64
/* Location of the bad-block label */
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	0
/* Extra address cycle for > 128MiB */
#define CONFIG_SYS_NAND_5_ADDR_CYCLE

/* Size of the block protected by one OOB (Spare Area in Samsung terminology) */
#define CONFIG_SYS_NAND_ECCSIZE	CONFIG_SYS_NAND_PAGE_SIZE
/* Number of ECC bytes per OOB - S3C6400 calculates 4 bytes ECC in 1-bit mode */
#define CONFIG_SYS_NAND_ECCBYTES	4
/* Number of ECC-blocks per NAND page */
#define CONFIG_SYS_NAND_ECCSTEPS	(CONFIG_SYS_NAND_PAGE_SIZE / CONFIG_SYS_NAND_ECCSIZE)
/* Size of a single OOB region */
#define CONFIG_SYS_NAND_OOBSIZE	64
/* Number of ECC bytes per page */
#define CONFIG_SYS_NAND_ECCTOTAL	(CONFIG_SYS_NAND_ECCBYTES * CONFIG_SYS_NAND_ECCSTEPS)
/* ECC byte positions */
#define CONFIG_SYS_NAND_ECCPOS		{40, 41, 42, 43, 44, 45, 46, 47, \
				 48, 49, 50, 51, 52, 53, 54, 55, \
				 56, 57, 58, 59, 60, 61, 62, 63}

//#define CONFIG_SYS_S3C_NAND_HWECC
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x70200010
#define CONFIG_BOOT_NAND
#define CONFIG_NAND
#define CONFIG_NAND_S3C64XX
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS

//#define CONFIG_SYS_NAND_PAGE_SIZE	(2 * 1024)
//#define CONFIG_SYS_NAND_PAGE_COUNT	64
//#define CONFIG_SYS_NAND_BLOCK_SIZE	(CONFIG_SYS_NAND_PAGE_SIZE * CONFIG_SYS_NAND_PAGE_COUNT)

#define CONFIG_SYS_NAND_U_BOOT_DST	0x5fc00000
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_NAND_U_BOOT_DST

#define CONFIG_SYS_NAND_U_BOOT_OFFS	(4 * 1024)
#define CONFIG_SYS_NAND_U_BOOT_SIZE	(1024 * 1024)

#define CONFIG_DOS_PARTITION	1

#define CONFIG_RBTREE
#define CONFIG_YAFFS2
#define CONFIG_YAFFS_NO_YAFFS1
#define YAFFS_CHUNKS_PER_BLOCK 128
#define YAFFS_BYTES_PER_CHUNK 2048
#define YAFFS_BYTES_PER_SPARE 64



//#define CONFIG_CMD_MMC
//#define CFG_MMC_BASE		(0xf0000000)
//#define CFG_MAX_MMC_DEVICE	1

//#define CONFIG_CMD_USB
#define CONFIG_USB_GADGET
#define CONFIG_USB_GADGET_S3C_UDC_OTG
//#define CONFIG_USB_CDC

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr2=0x51000000\0" \
	"bb=run setinitrdargs;tftp ${loadaddr} uImagebb;bootm ${loadaddr}\0" \
	"upuboot=tftp ${loadaddr} u-boot-nand.bin;nand erase 0 80000;nand write ${loadaddr} 0 80000;reset\0" \
    "upkernel=tftp ${loadaddr} uImage;nand erase.part kernel;nand write ${loadaddr} kernel\0" \
    "uprecovery=tftp ${loadaddr2} recovery.img;nand erase.part recovery;nand write ${loadaddr2} recovery\0" \
    "fbparts=0xc0000@0x0(uboot),0x40000@0xc0000(env),0x700000@0x100000(kernel),0x800000@0x800000(recovery),0xf000000@0x1000000(system)yaffs,0x28000000@0x10000000(data)yaffs,0x8000000@0x38000000(cache)yaffs\0" \
    "mtdparts=mtdparts=nand0:0xc0000@0x0(uboot),0x40000@0xc0000(env),0x700000@0x100000(kernel),0x800000@0x800000(recovery),0xf000000@0x1000000(system),0x28000000@0x10000000(data),0x8000000@0x38000000(cache)\0" \
    "mtdids=nand0=nand0\0" \
	"video=video=fb:WX4300F\0" \
	"rootdevnand=root=/dev/mtdblock4 rootfstype=yaffs2\0" \
	"nfsroot=/home/devel/real6410/root_mkfs,nfsvers=3\0" \
	"ip=ip=192.168.0.91:192.168.0.2:192.168.0.1:255.255.255.0:real6410:eth0:off\0" \
	"rootdevnfs=root=/dev/nfs nfsroot=${serverip}:${nfsroot}rootfstype=yaffs2\0" \
    "setnfsargs=setenv bootargs noinitrd mem=${mem} console=${cons} init=/init root=/dev/nfs nfsroot=${serverip}:${nfsroot} ${ip} ${video}\0" \
    "setinitrdargs=setenv bootargs mem=${mem} console=${cons} rdinit=/linuxrc\0" \
	"setramdiskargs=setenv bootargs mem=${mem} console=${cons} init=/init root=/dev/ram rw\0" \
	"setnandargs=setenv bootargs noinitrd mem=${mem} console=${cons} init=/init ${rootdevnand}\0" \
    "initrdtftpboot=run setinitrdargs;tftp ${loadaddr2} zRecovery;bootm ${loadaddr2}\0" \
    "recoveryboot=run setramdiskargs;nand read ${loadaddr2} recovery;bootm ${loadaddr2}\0" \
    "bbtftpboot=run setinitrdargs;tftp ${loadaddr} uImagebb;bootm ${loadaddr}\0" \
	"cons=ttySAC0,115200\0" \
	"mem=224M\0"

#define MTDPARTS_DEFAULT  "mtdparts=nand0:0xc0000@0x0(uboot),0x40000@0xc0000(env),0x700000@0x100000(kernel),0x800000@0x800000(recovery),0xf000000@0x1000000(system),0x28000000@0x10000000(data),0x8000000@0x38000000(cache)"
#define MTDIDS_DEFAULT "nand0=nand0"

#define CONFIG_CMD_FASTBOOT

#define	CONFIG_FASTBOOT /* Android fast boot */

#ifdef	CONFIG_FASTBOOT
/* Fastboot settings
 */
/* Another macro may also be used or instead used to take care of the case
 * where fastboot is started at boot (to be incorporated) based on key press
 */
#define	CONFIG_CMD_FASTBOOT
#define	CONFIG_FASTBOOT_TRANSFER_BUFFER		((unsigned char *)0x50000000)
#define	CONFIG_FASTBOOT_TRANSFER_BUFFER_SIZE	(0x0F000000)
/* if already present, use already existing NAND macros for block & oob size */
#define	FASTBOOT_NAND_BLOCK_SIZE		2048
#define	FASTBOOT_NAND_OOB_SIZE			64


#endif /* CONFIG_FASTBOOT */

/* USB device configuration */
#define CONFIG_USB_DEVICE		1
//#define CONFIG_USB_TTY			1
//#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1
/* Change these to suit your needs */
#define CONFIG_FASTBOOT_VENDORID		0x0bb4
#define CONFIG_FASTBOOT_PRODUCTID		0x0c01
#define CONFIG_FASTBOOT_MANUFACTURER	"Samsung"
#define CONFIG_FASTBOOT_PRODUCT_NAME	"S3C6410"
#define CONFIG_FASTBOOT_SERIAL		"R6410"

#define CONFIG_LCD_FRAMEBUFFER 0x5fb00000
//#define CONFIG_LCD
// Added upd command to update uboot
#define CONFIG_CMD_UPUBOOT
#define CONFIG_CMD_READKEY

#define CONFIG_ANDROID_BOOT_IMAGE

//#define CONFIG_CMD_GPIO

#endif	/* __CONFIG_H */
