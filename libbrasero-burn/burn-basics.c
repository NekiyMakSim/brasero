/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * Libbrasero-burn
 * Copyright (C) Philippe Rouquier 2005-2009 <bonfire-app@wanadoo.fr>
 *
 * Libbrasero-burn is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The Libbrasero-burn authors hereby grant permission for non-GPL compatible
 * GStreamer plugins to be used and distributed together with GStreamer
 * and Libbrasero-burn. This permission is above and beyond the permissions granted
 * by the GPL license by which Libbrasero-burn is covered. If you modify this code
 * you may extend this exception to your version of the code, but you are not
 * obligated to do so. If you do not wish to do so, delete this exception
 * statement from your version.
 * 
 * Libbrasero-burn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */
#include <string.h>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <glib.h>
#include <glib/gi18n-lib.h>
#include <glib/gstdio.h>

#include "burn-basics.h"
#include "burn-debug.h"
#include "burn-caps.h"
#include "burn-plugin-manager.h"
#include "burn-plugin-private.h"

#include "brasero-drive.h"
#include "brasero-medium-monitor.h"

static BraseroPluginManager *plugin_manager = NULL;
static BraseroMediumMonitor *medium_manager = NULL;

/**
 * This is defined in burn-caps.c it's for debugging mainly
 */

void brasero_caps_list_dump (void);

GQuark
brasero_burn_quark (void)
{
	static GQuark quark = 0;

	if (!quark)
		quark = g_quark_from_static_string ("BraseroBurnError");

	return quark;
}
 
const gchar *
brasero_burn_action_to_string (BraseroBurnAction action)
{
	gchar *strings [BRASERO_BURN_ACTION_LAST] = { 	"",
							N_("Getting size"),
							N_("Creating image"),
							N_("Writing"),
							N_("Blanking"),
							N_("Creating checksum"),
							N_("Copying disc"),
							N_("Copying file"),
							N_("Analysing audio files"),
							N_("Transcoding song"),
							N_("Preparing to write"),
							N_("Writing leadin"),
							N_("Writing CD-TEXT information"),
							N_("Finalising"),
							N_("Writing leadout"),
						        N_("Starting to record"),
							N_("Success") };
	return _(strings [action]);
}

/**
 * Two utility functions
 */

gchar *
brasero_string_get_localpath (const gchar *uri)
{
	gchar *localpath;
	gchar *realuri;
	GFile *file;

	if (!uri)
		return NULL;

	if (uri [0] == '/')
		return g_strdup (uri);

	if (strncmp (uri, "file://", 7))
		return NULL;

	file = g_file_new_for_commandline_arg (uri);
	realuri = g_file_get_uri (file);
	g_object_unref (file);

	localpath = g_filename_from_uri (realuri, NULL, NULL);
	g_free (realuri);

	return localpath;
}

gchar *
brasero_string_get_uri (const gchar *uri)
{
	gchar *uri_return;
	GFile *file;

	if (!uri)
		return NULL;

	if (uri [0] != '/')
		return g_strdup (uri);

	file = g_file_new_for_commandline_arg (uri);
	uri_return = g_file_get_uri (file);
	g_object_unref (file);

	return uri_return;
}

gboolean
brasero_burn_library_start (void)
{
	BRASERO_BURN_LOG ("Initializing Brasero-%i.%i.%i",
			  BRASERO_MAJOR_VERSION,
			  BRASERO_MINOR_VERSION,
			  BRASERO_SUB);

	/* initialize the media library */
	brasero_media_library_start ();

	/* initialize all device list */
	if (!medium_manager)
		medium_manager = brasero_medium_monitor_get_default ();

	/* initialize plugins */
	brasero_burn_caps_get_default ();

	if (!plugin_manager)
		plugin_manager = brasero_plugin_manager_get_default ();

	brasero_caps_list_dump ();
	return TRUE;
}

GSList *
brasero_burn_library_get_plugins_list (void)
{
	plugin_manager = brasero_plugin_manager_get_default ();
	return brasero_plugin_manager_get_plugins_list (plugin_manager);
}

void
brasero_burn_library_stop (void)
{
	if (plugin_manager) {
		g_object_unref (plugin_manager);
		plugin_manager = NULL;
	}

	if (medium_manager) {
		g_object_unref (medium_manager);
		medium_manager = NULL;
	}

	/* close HAL connection */
//	brasero_hal_watch_destroy ();
}
