/*
 * (C) Copyright 2010
 * Texas Instruments Incorporated - http://www.ti.com/
 *
 * Aneesh V <aneesh@ti.com>
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
#ifndef PL310_H
#define PL310_H

#include <linux/types.h>

/* Register offsets */
#define PL310_CACHE_TYPE		0x004
#define PL310_AUX_CTRL			0x104

#define PL310_CACHE_SYNC		0x730
#define PL310_INVAL_LINE_PA		0x770
#define PL310_INVAL_WAY			0x77C
#define PL310_CLEAN_LINE_PA		0x7B0
#define PL310_CLEAN_INVAL_WAY		0x7FC
#define PL310_CLEAN_INVAL_LINE_PA	0x7F0

/* Register bit fields */
#define PL310_AUX_CTRL_ASSOCIATIVITY_MASK	(1 << 16)

void pl310_inval_all(void);
void pl310_clean_inval_all(void);
void pl310_inval_range(u32 start, u32 end);
void pl310_clean_inval_range(u32 start, u32 end);

#endif
