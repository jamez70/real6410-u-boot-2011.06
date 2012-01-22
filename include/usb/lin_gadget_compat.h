/*
 * Copyright (c) 2011 Samsung Electronics
 * Lukasz Majewski <l.majewski at samsung.com>
 *
 * This is a Linux kernel compatibility layer for USB Gadget
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 begin_of_the_skype_highlighting            02111-1307      end_of_the_skype_highlighting USA
 */

#ifndef __LIN_COMPAT_H__
#define __LIN_COMPAT_H__

/* common */
typedef int	spinlock_t;
typedef int	wait_queue_head_t;
typedef int	irqreturn_t;
#define spin_lock_init(...)
#define spin_lock(...)
#define spin_lock_irqsave(lock, flags) do {flags = 1; } while (0)
#define spin_unlock(...)
#define spin_unlock_irqrestore(lock, flags) do {flags = 0; } while (0)
#define disable_irq(...)
#define enable_irq(...)

#define mutex_init(...)
#define mutex_lock(...)
#define mutex_unlock(...)

#define WARN_ON(x) if (x) {printf("WARNING in %s line %d\n" \
				  , __FILE__, __LINE__); }

#define printk printf

#define KERN_WARNING
#define KERN_ERR
#define KERN_NOTICE
#define KERN_DEBUG

#define GFP_KERNEL	0

#define IRQ_HANDLED	1

#define ENOTSUPP	524	/* Operation is not supported */

#define EXPORT_SYMBOL(x)

#define kmalloc(size, type) malloc(size)
#define kfree(addr) free(addr)
#define mdelay(n) ({unsigned long msec = (n); while (msec--) udelay(1000); })

#define __iomem

#endif /* __LIN_COMPAT_H__ */
