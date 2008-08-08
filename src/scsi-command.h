/***************************************************************************
 *            burn-scsi-command.h
 *
 *  Thu Oct 19 17:32:51 2006
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

#include "scsi-device.h"
#include "scsi-error.h"
#include "scsi-utils.h"
#include "scsi-base.h"

#ifndef _BURN_SCSI_COMMAND_H
#define _BURN_SCSI_COMMAND_H

G_BEGIN_DECLS

/* Most scsi commands are <= 16 (apparently some of the new mmc can be longer) */
#define BRASERO_SCSI_CMD_MAX_LEN	16
	
typedef enum {
	BRASERO_SCSI_WRITE	= 1,
	BRASERO_SCSI_READ	= 1 << 1
} BraseroScsiDirection;

struct _BraseroScsiCmdInfo {
	int size;
	uchar opcode;
	BraseroScsiDirection direction;
};
typedef struct _BraseroScsiCmdInfo BraseroScsiCmdInfo;

#define BRASERO_SCSI_COMMAND_DEFINE(cdb, name, direction)			\
static const BraseroScsiCmdInfo info =						\
{	/* SCSI commands always end by 1 byte of ctl */				\
	G_STRUCT_OFFSET (cdb, ctl) + 1, 					\
	BRASERO_##name##_OPCODE,						\
	direction								\
}

gpointer
brasero_scsi_command_new (const BraseroScsiCmdInfo *info,
			  BraseroDeviceHandle *handle);

BraseroScsiResult
brasero_scsi_command_free (gpointer command);

BraseroScsiResult
brasero_scsi_command_issue_sync (gpointer command,
				 gpointer buffer,
				 int size,
				 BraseroScsiErrCode *error);
G_END_DECLS

#endif /* _BURN_SCSI_COMMAND_H */

 
