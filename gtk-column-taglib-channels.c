/*
 * gtk-column-taglib-channels.c
 *
 * Copyright (C) 2016 Alessandro Grassi <alessandro.g89@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <libfm/fm.h>
#include <libfm/fm-gtk.h>
#include <taglib/tag_c.h>

FM_DEFINE_MODULE(gtk_folder_col, taglib_channels)

GType get_type() { return G_TYPE_STRING; };

void get_value(FmFileInfo *fi, GValue *value){
	
	char* filename;
	int channels;
	char channels_string[15];
	TagLib_File *TL_file;
	
	filename = fm_path_to_str( fm_file_info_get_path(fi) );
	TL_file = taglib_file_new( filename );
	free( filename );
	
	if (TL_file != NULL) {
		if(taglib_file_is_valid(TL_file)){
			const TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file );
			channels = taglib_audioproperties_channels( TL_props );
			switch( channels ){
				case 1:  sprintf( channels_string, "Mono" ); break;
				case 2:  sprintf( channels_string, "Stereo" ); break;
				default: sprintf( channels_string, "%d channels", channels ); break;
			}
			
			g_value_set_string( value, channels_string );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file );
		}
	}
};

gint sort(FmFileInfo *fi1, FmFileInfo *fi2){
	char *filename1, *filename2;
	int channels1 = 0, channels2 = 0;
	TagLib_File *TL_file1, *TL_file2;
	
	filename1 = fm_path_to_str( fm_file_info_get_path(fi1) );
	filename2 = fm_path_to_str( fm_file_info_get_path(fi2) );
	TL_file1 = taglib_file_new( filename1 );
	TL_file2 = taglib_file_new( filename2 );
	free( filename1 );
	free( filename2 );
	
	if (TL_file1 != NULL) {
		if(taglib_file_is_valid(TL_file1)){
			const TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file1 );
			channels1 = taglib_audioproperties_channels( TL_props );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file1 );
		}
	}
	
	if (TL_file2 != NULL) {
		if(taglib_file_is_valid(TL_file2)){
			const TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file2 );
			channels2 = taglib_audioproperties_channels( TL_props );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file2 );
		}
	}
	
	return channels1 - channels2;
}

FmFolderModelColumnInit fm_module_init_gtk_folder_col = {
	"Channels",
	0, 
	&get_type,
	&get_value,
	&sort
};
