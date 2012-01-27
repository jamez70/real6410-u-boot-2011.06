/*
 * (C) Copyright 2010
 * Darius Augulis, <augulis.darius@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
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

#include <common.h>
#include <netdev.h>
#include <asm/arch/s3c6400.h>
#include <asm/arch/hs_otg.h>
#include <asm/io.h>
#include "rlogo.h"

int s3c_udc_probe(struct s3c_plat_otg_data *pdata);

/* ------------------------------------------------------------------------- */

DECLARE_GLOBAL_DATA_PTR;

static inline void delay(unsigned long loops)
{
	__asm__ volatile ("1:\n" "subs %0, %1, #1\n"
			  "bne 1b"
			  : "=r" (loops) : "0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */

#define DM9000_Tacs     (0x0)   // 0clk         address set-up
#define DM9000_Tcos     (0x4)   // 4clk         chip selection set-up
#define DM9000_Tacc     (0xE)   // 14clk        access cycle
#define DM9000_Tcoh     (0x1)   // 1clk         chip selection hold
#define DM9000_Tah      (0x4)   // 4clk         address holding time
#define DM9000_Tacp     (0x6)   // 6clk         page mode access cycle
#define DM9000_PMC      (0x0)   // normal(1data)page mode configuration

#define S3C6410_PHY_BASE (0x7c100000)
#define S3C6410_OTG_BASE (0x7c000000)

// DMA0 75000000
// DMA1 75100000
// SDMA0 7db00000
// SDMA1 7dc00000
#define DMACConfig1 __REG(0x75000030)
#define DMACConfig2 __REG(0x75100030)
#define DMACConfig3 __REG(0x7db00030)
#define DMACConfig4 __REG(0x7dc00030)

static void dm9000_pre_init(void)
{
	SROM_BW_REG &= ~(0xf << 4);
	SROM_BW_REG |= (1 << 7) | (1 << 6) | (1 << 4);
	SROM_BC1_REG = ((DM9000_Tacs << 28) + (DM9000_Tcos << 24 ) +
			(DM9000_Tacc << 16) + (DM9000_Tcoh << 12) +
			(DM9000_Tah << 8) + (DM9000_Tacp << 4) + (DM9000_PMC));

}

#ifdef CONFIG_USB_GADGET

static int s3c6410_phy_control(int on)
{
	if (on)
		printf("PHY ON\n");
	else
		printf("PHY OFF\n");
}

struct s3c_plat_otg_data s3c64xx_otg_data = {
	.phy_control = s3c6410_phy_control,
	.regs_phy = S3C6410_PHY_BASE,
	.regs_otg = S3C6410_OTG_BASE,
};
#endif

void board_gpio_init(void)
{
	u32 val;
	
	__raw_writel(0,0x7410800c);		// MOFPCON
	val=readl(0x7f0081a0);
	val &= ~3;
	val |= 1;
	__raw_writel(val,0x7f0081a0);
	// Set the GPIO for LCD
	__raw_writel(0xaaaaaaaa,0x7f008100);
	__raw_writel(0xaaaaaaaa,0x7f008120);

}

#define LCDWRITE(a,b)  __raw_writel(b,a)

void board_lcd_logo(void)
{
	unsigned short *src = (unsigned short *)rlogo_bmp;
	int x,y;
	unsigned short *scr;
	
	for (y=0; y<50; y++)
	{
		scr=(unsigned short *)((960*(y+111))+0x5ffc0000+320);
		for (x=0;x<160; x++)
		{
			*scr++=*src++;
		}
	}
	
}

void board_lcd_init(void)
{
	u32 v,i;
	u32 *p;
	LCDWRITE(0x77100004,0x00f0c060);
	LCDWRITE(0x77100010,0x00000000);
	LCDWRITE(0x77100014,0x00020127);
	LCDWRITE(0x77100018,0x000879df);
	LCDWRITE(0x77100020,0x00010015);
	LCDWRITE(0x77100044,0x000f010f);
	LCDWRITE(0x77100048,0x0001fe00);
	LCDWRITE(0x771000a0,CONFIG_LCD_FRAMEBUFFER);
	LCDWRITE(0x771000a4,CONFIG_LCD_FRAMEBUFFER);
	LCDWRITE(0x771000d0,0x0043fc00);
	LCDWRITE(0x771000d4,0x0043fc00);
	LCDWRITE(0x77100100,0x3c0);
	LCDWRITE(0x771001a0,0x00000006);
	LCDWRITE(0x77100130,0x03f00000);
	LCDWRITE(0x77100100,0x000003c0);
	LCDWRITE(0x77100140,0x00ffffff);
	LCDWRITE(0x77100144,0x00ffffff);
	LCDWRITE(0x77100148,0x00ffffff);
	LCDWRITE(0x7710014c,0x00ffffff);
	LCDWRITE(0x77100150,0x00ffffff);
	LCDWRITE(0x77100154,0x00ffffff);
	LCDWRITE(0x77100158,0x00ffffff);
	LCDWRITE(0x7710015c,0x00ffffff);
	LCDWRITE(0x77100000,0x00000393);	
	p = (u32 *)(CONFIG_LCD_FRAMEBUFFER);
	v = 0;
	for (i=0; i<(272*480/2); i++)
		*p++ = v;
	board_lcd_logo();
}

int board_init(void)
{
	dm9000_pre_init();
	OTHERS_REG |= 0x10000;
	// Enable DMA
	DMACConfig1 = 1;
	DMACConfig2 = 1;
	DMACConfig3 = 1;
	DMACConfig4 = 1;
	gd->bd->bi_arch_number = MACH_TYPE;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	board_gpio_init();
	board_lcd_init();
	return 0;
}

void s3c_start_usb(void)
{
	s3c_udc_probe(&s3c64xx_otg_data);
}

int board_late_init(void)
{
	s3c_start_usb();
	return 0;
}


int dram_init (void)
{
        /* dram_init must store complete ramsize in gd->ram_size */
        gd->ram_size = get_ram_size((volatile void *)PHYS_SDRAM_1,
                                PHYS_SDRAM_1_SIZE);
        return 0;
}

void dram_init_banksize(void)
{
        gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
        gd->bd->bi_dram[0].size = get_ram_size((volatile void *)PHYS_SDRAM_1,
                        PHYS_SDRAM_1_SIZE);
}

#ifdef CONFIG_DISPLAY_BOARDINFO
int checkboard(void)
{
	printf("\x1b[1;32mBoard:   \x1b[1;33mREAL6410\x1b[0m\n");
	return 0;
}
#endif

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	return dm9000_initialize(bis);
}
#endif


