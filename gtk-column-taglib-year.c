/*
 * gtk-column-taglib-year.c
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

FM_DEFINE_MODULE(gtk_folder_col, taglib_year)

GType get_type() { return G_TYPE_STRING; };

void get_value(FmFileInfo *fi, GValue *value){
	
	char* filename;
	int year;
	char year_string[10];
	TagLib_File *TL_file;
	TagLib_Tag *TL_tag;
	
	filename = fm_path_to_str( fm_file_info_get_path(fi) );
	TL_file = taglib_file_new( filename );
	free( filename );
	
	if (TL_file != NULL) {
		if(taglib_file_is_valid(TL_file)){
			TL_tag = taglib_file_tag( TL_file );
			year = taglib_tag_year( TL_tag );
			if( year !=0 ){
				sprintf( year_string, "%d", year );
				g_value_set_string( value, year_string );
			}
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file );
		}
	}
};

gint sort(FmFileInfo *fi1, FmFileInfo *fi2){
	char *filename1, *filename2;
	int year1 = 0, year2 = 0;
	TagLib_File *TL_file1, *TL_file2;
	
	filename1 = fm_path_to_str( fm_file_info_get_path(fi1) );
	filename2 = fm_path_to_str( fm_file_info_get_path(fi2) );
	TL_file1 = taglib_file_new( filename1 );
	TL_file2 = taglib_file_new( filename2 );
	free( filename1 );
	free( filename2 );
	
	if (TL_file1 != NULL) {
		if(taglib_file_is_valid(TL_file1)){
			TagLib_Tag *TL_tag = taglib_file_tag( TL_file1 );
			year1 = taglib_tag_year( TL_tag );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file1 );
		}
	}
	
	if (TL_file2 != NULL) {
		if(taglib_file_is_valid(TL_file2)){
			TagLib_Tag *TL_tag = taglib_file_tag( TL_file2 );
			year2 = taglib_tag_year( TL_tag );
			
			taglib_tag_free_strings();
			taglib_file_free( TL_file2 );
		}
	}
	
	return year1 - year2;
}

FmFolderModelColumnInit fm_module_init_gtk_folder_col = {
	"Year",
	0, 
	&get_type,
	&get_value,
	&sort
};
