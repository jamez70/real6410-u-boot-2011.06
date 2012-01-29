/*
 * (C) Copyright 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

/*
 * Misc functions
 */
#include <common.h>
#include <command.h>

extern u32 board_read_keyboard(void);


int do_readkey (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 ret;
	u32 mask;
	
	mask = 0xffffffff;
	if (argc == 2)
		mask = simple_strtoul(argv[1],NULL,16);
	ret=board_read_keyboard();
	printf("Read value 0x%x, masked 0x%x\n",ret,ret&mask);
	return ret & mask;
}

U_BOOT_CMD(
	readkey ,    2,    1,     do_readkey,
	"update uboot",
	"[mask]\n"
	"       - read the key on the keypad\n"
);
