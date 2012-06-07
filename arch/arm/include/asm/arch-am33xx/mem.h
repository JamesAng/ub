/*
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

#ifndef _MEM_H_
#define _MEM_H_

#define GPMC_MAX_CS	8
#define GPMC_MAX_REG	7

#define M_NAND_GPMC_CONFIG1	0x00000800
#define M_NAND_GPMC_CONFIG2 	0x001e1e00
#define M_NAND_GPMC_CONFIG3 	0x001e1e00
#define M_NAND_GPMC_CONFIG4 	0x16051807
#define M_NAND_GPMC_CONFIG5 	0x00151e1e
#define M_NAND_GPMC_CONFIG6	0x16000f80
#define M_NAND_GPMC_CONFIG7	0x00000008

#define GPMC_SIZE_256M		0x0
#define GPMC_SIZE_128M		0x8
#define GPMC_SIZE_64M		0xC
#define GPMC_SIZE_32M		0xE
#define GPMC_SIZE_16M		0xF

#define PISMO1_NAND_BASE	NAND_BASE
#define PISMO1_NAND_SIZE	GPMC_SIZE_256M

#endif /* endif _MEM_H_ */
