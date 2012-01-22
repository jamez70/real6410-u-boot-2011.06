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

extern int do_run(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

int do_upuboot (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *updscr[2]  = { "run", "upuboot" };		
	char scrname[32];
	int ret;
	
	if (argc == 2)
	{
		sprintf(scrname,"up%s",argv[1]);
		updscr[1] = scrname;
	}
	if (getenv(updscr[1]) == NULL)
	{
		printf("Could not run script '%s'\n",updscr[1]);
		return 1;
	}
	
	ret=do_run(NULL, 0, 2, updscr);
	return ret;
}

U_BOOT_CMD(
	upd ,    2,    1,     do_upuboot,
	"update uboot",
	"[script]\n"
	"       - update uboot by running 'upuboot'\n"
	"       - script will run 'up[script]'"
);
