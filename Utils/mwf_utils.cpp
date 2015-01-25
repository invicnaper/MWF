/*
 _   _  _ _ _  ___ 
| \_/ || | | || __|
| \_/ || V V || _| 
|_| |_| \_n_/ |_|  

@author : naper
@description : c++ web framework
GNU LESSER GENERAL PUBLIC LICENSE

                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.


  This version of the GNU Lesser General Public License incorporates
the terms and conditions of version 3 of the GNU General Public
License, supplemented by the additional permissions listed below.

  0. Additional Definitions.

  As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the GNU
General Public License.

  "The Library" refers to a covered work governed by this License,
other than an Application or a Combined Work as defined below.

  An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

  A "Combined Work" is a work produced by combining or linking an
Application with the Library.  The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".
*/

#include "../Headers/mwf.h"

/*
	Function:
	description:
*/
void Mw::Html::link(const char* string, const char* href, const char* style = NULL){
	if(style == NULL)
		std::cout << "<a href='" << href << "'>" << string << "</a>";
	else
		std::cout << "<a href='" << href << "' class = '"<< style << "'>" << string << "</a>";

}
/*
	Function:
	description:
*/
void Mw::Html::p(const char* string, const char* style = NULL){
	if(style == NULL)
		std::cout << "<p>" << string << "</p>";
	else
		std::cout << "<p class = '"<< style << "'>" << string << "</p>";

}
/*
	Function:
	description:
*/
void Mw::Html::h(const char* string, int type, const char* style = NULL){
	if(style == NULL)
		std::cout << "<h"<< type << ">" << string << "</h"<< type <<">";
	else
		std::cout << "<h"<< type << " class = '" << style << "'>" << string << "</h"<< type <<">";

}
void Mw::Html::img(const char* src, int height, int width){
	if(height == 0 && width == 0)
		std::cout << "<img src='"<< src <<" />";
	else
		std::cout << "<img src='"<< src <<" width='" << width << "' height='" << height << "'/>";

}
void Mw::Html::checkbox(char* string, const char* style){
	if (style == NULL)
		cgiFormCheckboxSingle(string);
	else
		cgiFormCheckboxSingle(string);/* add style */
}
void Mw::Html::code(const char* string, const char* style){
	if(style == NULL)
		std::cout << "<p><code>" << string << "</code></p>";
	else
		std::cout << "<p><code class='"<< style <<"'>" << string << "</code></p>";
}
void Mw::Html::css_local(const char * file, const char* type){
	Mw::Utils utils;
	FILE * css;
	css = NULL;
	css = fopen(file,"r");
	if(!css){
		utils.error("CSS file not found","css","css_local", __LINE__);
	}else{
		std::cout << "<link rel='stylesheet' type = '" << type << "'  href = '" << file << "'></link>";
	}
	fclose(css);
}
void Mw::Html::css_web(const char * file, const char* type){
	std::cout << "<link rel='stylesheet' type = '" << type << "'  href = '" << file << "'></link>";
}
void Mw::Html::js_local(const char * file){
	Mw::Utils utils;
	FILE * js;
	js = NULL;
	js = fopen(file,"r");
	if(!js){
		utils.error("JS file not found","js","css_local", __LINE__);
	}else{
		std::cout << "<script src = '" << file << "'></script>";
	}
	fclose(js);
}
void Mw::Html::js_web(const char * file){
	//std::cout << "<link rel='stylesheet' type = '" << type << "'  href = '" << file << "'></link>";
}