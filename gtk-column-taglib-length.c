/*
 * gtk-column-taglib-length.c
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

FM_DEFINE_MODULE(gtk_folder_col, taglib_length)

GType get_type() { return G_TYPE_STRING; };

void get_value(FmFileInfo *fi, GValue *value){
	
	char* filename;
	int length;
	char length_string[12];
	TagLib_File *TL_file;
	
	filename = fm_path_to_str( fm_file_info_get_path(fi) );
	TL_file = taglib_file_new( filename );
	free( filename );
	
	if (TL_file != NULL) {
		if(taglib_file_is_valid(TL_file)){
			const TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file );
			length = taglib_audioproperties_length( TL_props );
			if( length>3600 ){
				sprintf( length_string, "%d:%02d:%02d", length/3600, (length%3600)/60, length%60 );
			}else{
				sprintf( length_string, "%d:%02d", length/60, length%60 );
			}
			g_value_set_string( value, length_string );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file );
		}
	}
};

gint sort(FmFileInfo *fi1, FmFileInfo *fi2){
	char *filename1, *filename2;
	int length1 = 0, length2 = 0;
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
			length1 = taglib_audioproperties_length( TL_props );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file1 );
		}
	}
	
	if (TL_file2 != NULL) {
		if(taglib_file_is_valid(TL_file2)){
			const TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file2 );
			length2 = taglib_audioproperties_length( TL_props );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file2 );
		}
	}
	
	return length1 - length2;
}

FmFolderModelColumnInit fm_module_init_gtk_folder_col = {
	"Length",
	0, 
	&get_type,
	&get_value,
	&sort
};
