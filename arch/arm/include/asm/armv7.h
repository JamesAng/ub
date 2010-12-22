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
#ifndef ARMV7_H
#define ARMV7_H

#include <linux/types.h>

/*
 * Values for InD field in CSSELR
 * Selects the type of cache
 */
#define ARMV7_CSSELR_IND_DATA_UNIFIED	0
#define ARMV7_CSSELR_IND_INSTRUCTION	1

/* Values for Ctype fields in CLIDR */
#define ARMV7_CLIDR_CTYPE_NO_CACHE		0
#define ARMV7_CLIDR_CTYPE_INSTRUCTION_ONLY	1
#define ARMV7_CLIDR_CTYPE_DATA_ONLY		2
#define ARMV7_CLIDR_CTYPE_INSTRUCTION_DATA	3
#define ARMV7_CLIDR_CTYPE_UNIFIED		4

/* some utility macros */
#define mask(start, end) \
	(((1 << ((end) - (start) + 1)) - 1) << (start))

#define mask_n_get(reg, start, end) \
	(((reg) & mask(start, end)) >> (start))

struct v7_outer_cache_ops {
	void (*enable)(void);
	void (*disable)(void);
	void (*flush_all)(void);
	void (*inval_all)(void);
	void (*flush_range)(u32 start, u32 end);
	void (*inval_range)(u32 start, u32 end);
};

extern struct v7_outer_cache_ops v7_outer_cache;

void v7_setup_outer_cache_ops(void);
#endif
