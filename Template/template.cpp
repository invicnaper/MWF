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

void Mw::Template::__load(const char* path){
	/* load xml or css template */
	Mw::Html html;
	if(strstr(path, "css")){
		html.css_web(path, "text/css");
	}
	if(strstr(path, "xml")){
		/* open xml file */
	}
}
void Mw::Template::errorStyle(){
	std::cout << "<style>";
	std::cout << "table.errors";
	std::cout << "{ width: 580px;";
	std::cout << "background-color: #FF0000;";
	std::cout << "border: 1px #000000 solid;";
	std::cout << "border-collapse: collapse;";
	std::cout << "border-spacing: 0px; }";
	std::cout << "td.errorDept";
	std::cout << "{ background-color: #FAAC58;";
	std::cout << "border: 1px #000000 solid;";
	std::cout << "font-family: Verdana;";
	std::cout << "font-weight: bold;";
	std::cout << "font-size: 12px;";
	std::cout << "color: #404040; }";
	std::cout << "td.error";
	std::cout << "{ border-bottom: 1px #6699CC dotted;";
	std::cout << "text-align: left;";
	std::cout << "font-family: Verdana, sans-serif, Arial;";
	std::cout << "font-weight: normal;";
	std::cout << "font-size: .7em;";
	std::cout << "color: #404040;";
	std::cout << "background-color: #fafafa;";
	std::cout << "padding-top: 4px;";
	std::cout << "padding-bottom: 4px;";
	std::cout << "padding-left: 8px;";
	std::cout << "padding-right: 0px; }";
	std::cout << "}";
	std::cout << "</style>";
}
void Mw::Template::show_notif(const char* content, const char* href_content, const char* href, int type){
	switch(type){
		case ERROR:
			std::cout <<  "<div class='alert alert-danger'>" << std::endl;
			std::cout <<  ""<< content << ". <a href='"<< href <<"' class='alert-link'>"<< href_content <<"</a></div>" << std::endl;
			break;
		default:

			break;
	}

}