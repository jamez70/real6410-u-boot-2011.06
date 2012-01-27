/*
 * (C) Copyright 2009 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
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

#ifndef __ASM_ARCH_GPIO_H
#define __ASM_ARCH_GPIO_H

#ifndef __ASSEMBLY__
struct s3c_gpio_bank1 {
	unsigned int	con;
	unsigned int	dat;
	unsigned int	pull;
	unsigned int	slp;
	unsigned int	slp_pull;
	unsigned char	res1[3];
};

struct s3c_gpio_bank2 {
	unsigned int	con;
	unsigned int    con2;
	unsigned int	dat;
	unsigned int	pull;
	unsigned int	slp;
	unsigned int	slp_pull;
	unsigned char	res1[2];
};

struct s3c_gpio {
	struct s3c_gpio_bank1 a;
	struct s3c_gpio_bank1 b;
	struct s3c_gpio_bank1 c;
	struct s3c_gpio_bank1 d;
	struct s3c_gpio_bank1 e; 
	struct s3c_gpio_bank1 f;
	struct s3c_gpio_bank1 g;
	struct s3c_gpio_bank2 h;
	struct s3c_gpio_bank1 i;
	struct s3c_gpio_bank1 j;
	struct s3c_gpio_bank2 k;
	struct s3c_gpio_bank2 l;
	struct s3c_gpio_bank1 m;
	struct s3c_gpio_bank1 n;
	struct s3c_gpio_bank1 o;
	struct s3c_gpio_bank1 p;
	struct s3c_gpio_bank1 q;
};

/* functions */
void gpio_cfg_pin(struct s3c_gpio_bank *bank, int gpio, int cfg);
void gpio_direction_output(struct s3c_gpio_bank *bank, int gpio, int en);
void gpio_direction_input(struct s3c_gpio_bank *bank, int gpio);
void gpio_set_value(struct s3c_gpio_bank *bank, int gpio, int en);
unsigned int gpio_get_value(struct s3c_gpio_bank *bank, int gpio);
void gpio_set_pull(struct s3c_gpio_bank *bank, int gpio, int mode);
void gpio_set_drv(struct s3c_gpio_bank *bank, int gpio, int mode);
void gpio_set_rate(struct s3c_gpio_bank *bank, int gpio, int mode);
#endif

/* Pin configurations */
#define GPIO_INPUT	0x0
#define GPIO_OUTPUT	0x1
#define GPIO_IRQ	0xf
#define GPIO_FUNC(x)	(x)

/* Pull mode */
#define GPIO_PULL_NONE	0x0
#define GPIO_PULL_DOWN	0x1
#define GPIO_PULL_UP	0x2

/* Drive Strength level */
#define GPIO_DRV_1X	0x0
#define GPIO_DRV_3X	0x1
#define GPIO_DRV_2X	0x2
#define GPIO_DRV_4X	0x3
#define GPIO_DRV_FAST	0x0
#define GPIO_DRV_SLOW	0x1

#define S3C_GPIO_BASE 0x7f008000

#endif
