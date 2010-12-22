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
#include <linux/types.h>
#include <asm/io.h>
#include <asm/armv7.h>
#include <asm/pl310.h>
#include <config.h>

static void pl310_cache_sync(void)
{
	__raw_writel(0, CONFIG_SYS_PL310_BASE + PL310_CACHE_SYNC);
}

static void pl310_background_op_all_ways(u32 op_reg_offset)
{
	u32 assoc_16, associativity, way_mask;
	assoc_16 = __raw_readl(CONFIG_SYS_PL310_BASE + PL310_AUX_CTRL) &
		   PL310_AUX_CTRL_ASSOCIATIVITY_MASK;

	if (assoc_16)
		associativity = 16;
	else
		associativity = 8;

	way_mask = (1 << associativity) - 1;
	/* Invalidate all ways */
	__raw_writel(way_mask, CONFIG_SYS_PL310_BASE + op_reg_offset);
	/* Wait for all ways to be invalidated */
	while (__raw_readl(CONFIG_SYS_PL310_BASE + op_reg_offset) && way_mask)
		;
	pl310_cache_sync();
}

void pl310_inval_all(void)
{
	pl310_background_op_all_ways(PL310_INVAL_WAY);
}

void pl310_clean_inval_all(void)
{
	pl310_background_op_all_ways(PL310_CLEAN_INVAL_WAY);
}

/* Flush(clean invalidate) memory from start to stop-1 */
void pl310_clean_inval_range(u32 start, u32 stop)
{
	/* PL310 currently supports only 32 bytes cache line */
	u32 pa, line_size = 32;

	/*
	 * Align to the beginning of cache-line - this ensures that
	 * the first 5 bits are 0 as required by PL310 TRM
	 */
	start &= ~(line_size - 1);

	for (pa = start; pa < stop; pa = pa + line_size)
		__raw_writel(pa, CONFIG_SYS_PL310_BASE +
			     PL310_CLEAN_INVAL_LINE_PA);
	pl310_cache_sync();
}

/* invalidate memory from start to stop-1 */
void pl310_inval_range(u32 start, u32 stop)
{
	/* PL310 currently supports only 32 bytes cache line */
	u32 pa, line_size = 32;

	/*
	 * If start address is not aligned to cache-line flush the first
	 * line to prevent affecting somebody else's buffer
	 */
	if (start & (line_size - 1)) {
		pl310_clean_inval_range(start, start + 1);
		/* move to next cache line */
		start = (start + line_size - 1) & ~(line_size - 1);
	}

	/*
	 * If stop address is not aligned to cache-line flush the last
	 * line to prevent affecting somebody else's buffer
	 */
	if (stop & (line_size - 1)) {
		pl310_clean_inval_range(stop, stop + 1);
		/* align to the beginning of this cache line */
		stop &= ~(line_size - 1);
	}

	for (pa = start; pa < stop; pa = pa + line_size)
		__raw_writel(pa, CONFIG_SYS_PL310_BASE +
			     PL310_INVAL_LINE_PA);
	pl310_cache_sync();
}
