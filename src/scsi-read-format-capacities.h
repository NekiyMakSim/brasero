/***************************************************************************
 *            scsi-read-format-capacities.h
 *
 *  Thu Nov  2 12:33:54 2006
 *  Copyright  2006  Rouquier Philippe
 *  <bonfire-app@wanadoo.fr>
 ****************************************************************************/

/*
 * Brasero is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Brasero is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include <glib.h>

#include "scsi-base.h"

#ifndef _SCSI_READ_FORMAT_CAPACITIES_H
#define _SCSI_READ_FORMAT_CAPACITIES_H

G_BEGIN_DECLS

typedef enum {
BRASERO_SCSI_DESC_UNFORMATTED		= 0x01,
BRASERO_SCSI_DESC_FORMATTED		= 0x02,
BRASERO_SCSI_DESC_NO_MEDIA		= 0x03
} BraseroScsiFormatCapacitiesDescType;

typedef enum {
BRASERO_SCSI_BLOCK_SIZE_DEFAULT_AND_DB		= 0x00,
BRASERO_SCSI_BLOCK_SIZE_SPARE_AREA		= 0x01,
	/* reserved */
BRASERO_SCSI_ZONE_FORMATTING_NUM		= 0x04,
BRASERO_SCSI_HIGHEST_ZONE_NUM			= 0x05,
	/* reserved */
BRASERO_SCSI_MAX_PACKET_SIZE_FORMAT		= 0x10,
BRASERO_SCSI_MAX_PACKET_SIZE_GROW_SESSION	= 0x11,
BRASERO_SCSI_MAX_PACKET_SIZE_ADD_SESSION	= 0x12,

BRASERO_SCSI_ECC_BLOCK_SIZE_GROW_SESSION	= 0x13,
BRASERO_SCSI_ECC_BLOCK_SIZE_ADD_SESSION		= 0x14,
BRASERO_SCSI_ECC_BLOCK_SIZE_FORMAT		= 0x15,
BRASERO_SCSI_HD_DVD_R				= 0x16,
	/* reserved */
BRASERO_SCSI_SPARING				= 0x20,
	/* reserved */
BRASERO_SCSI_MAX_DMA_NUM			= 0x24,
BRASERO_SCSI_DVDRW_PLUS				= 0x26
} BraseroScsiFormatCapacitiesParamType;

#if G_BYTE_ORDER == G_LITTLE_ENDIAN

struct _BraseroScsiMaxCapacityDesc{
	uchar blocks_num			[4];

	uchar type				:2;
	uchar reserved 				:6;

	uchar block_size			[3];
};

struct _BraseroScsiFormattableCapacityDesc{
	uchar blocks_num			[4];

	uchar reserved				:2;
	uchar format_type			:6;

	uchar type_param			[3];
};

#else

struct _BraseroScsiMaxCapacityDesc {
	uchar blocks_num			[4];

	uchar reserved 				:6;
	uchar type				:2;

	uchar block_size			[3];
};

struct _BraseroScsiFormattableCapacityDesc {
	uchar blocks_num			[4];

	uchar format_type			:6;
	uchar reserved				:2;

	uchar type_param			[3];
};

#endif

typedef struct _BraseroScsiMaxCapacityDesc BraseroScsiMaxCapacityDesc;
typedef struct _BraseroScsiFormattableCapacityDesc BraseroScsiFormattableCapacityDesc;

struct _BraseroScsiFormatCapacitiesHdr {
	uchar reserved				[3];
	uchar len;
	BraseroScsiMaxCapacityDesc max_caps	[1];
	BraseroScsiFormattableCapacityDesc desc	[0];
};
typedef struct _BraseroScsiFormatCapacitiesHdr BraseroScsiFormatCapacitiesHdr;

G_END_DECLS

#endif /* _SCSI_READ_FORMAT_CAPACITIES_H */

 
