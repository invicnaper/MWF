/*
* _   _  _ _ _  ___ 
*| \_/ || | | || __|
*| \_/ || V V || _| 
*|_| |_| \_n_/ |_|  
*
*@author : naper
*@description : c++ web framework
*
*                   GNU LESSER GENERAL PUBLIC LICENSE
*                       Version 3, 29 June 2007
*
* Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
* Everyone is permitted to copy and distribute verbatim copies
* of this license document, but changing it is not allowed.
*
*
*  This version of the GNU Lesser General Public License incorporates
*the terms and conditions of version 3 of the GNU General Public
*License, supplemented by the additional permissions listed below.
*
*  0. Additional Definitions.
*
*  As used herein, "this License" refers to version 3 of the GNU Lesser
*General Public License, and the "GNU GPL" refers to version 3 of the GNU
*General Public License.
*
*  "The Library" refers to a covered work governed by this License,
*other than an Application or a Combined Work as defined below.
*
*  An "Application" is any work that makes use of an interface provided
*by the Library, but which is not otherwise based on the Library.
*Defining a subclass of a class defined by the Library is deemed a mode
*of using an interface provided by the Library.
*
*  A "Combined Work" is a work produced by combining or linking an
*Application with the Library.  The particular version of the Library
*with which the Combined Work was made is also called the "Linked
*Version".
*/

#include "../Headers/mwf.h"

/*
	Function: __init
	description: init the web page
*/
void Mwu::Frame::init(const char* title,const char* description){
	/* init the web page */
	Mw::Template t;
	clock_t tStart = clock(); /* init timer */
	std::cout << "Content-Type: text/html;\n\n";
	std::cout << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" >\n\t<head>";
    std::cout << "\t\t<title>"<< title <<"</title>";
    std::cout << "\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\t</head>\n\t<body>";
    t.errorStyle();
}
/*
	Function: _GET
	description: get parametre from url
*/
char * Mw::Methods::GET(char* param, ...){
	Mw::Utils utils;
	Mw::Function f;
	int a = 0,i=0;
	char *result = NULL;
    char *data = getenv("QUERY_STRING");
    char *parsed = NULL;
    va_list arg; 
	va_start(arg, param);

	/* parse variable list */
	try{
		while(va_arg(arg,char *) != NULL){
			/* parse the list */
		}

    	if(data == NULL)
    	{
        	utils.error("Error with QUERY_STRING","query_string", "_GET", __LINE__);
    	}
    	parsed = strtok(data,"&");
		while( parsed ) {
			result = f.parsing_url(parsed, param);
			parsed = strtok((char *)0,"&");
		}
		if(strstr(result, "m") && strlen(result) == 3){
    		utils.error("can not found the param ","UNKNOWN_PARAM", "_GET", __LINE__);
    	}
    	va_end(arg);
    	return result;
    }
    catch(const char *error){
    	utils.error(error,"UNKNOWN ERROR", "_GET", __LINE__);
    }
}
/*
	Function: _GET
	description: get parametre from url ; return int
*/
int Mw::Methods::i_GET(char param[1025], ...){
	Mw::Utils utils;
	Mw::Function f;
	int a = 0,i=0;
	char *result = NULL;
    char *data = getenv("QUERY_STRING");
    char *parsed = NULL;
    va_list arg; 
	va_start(arg, param);

	/* parse variable list */
	try{
		while(va_arg(arg,char *) != NULL){
			/* parse the list */
		}

    	if(data == NULL)
    	{
        	utils.error("Error with QUERY_STRING","query_string", "i_GET", __LINE__);
    	}
    	parsed = strtok(data,"&");
		while( parsed ) {
			result = f.parsing_url(parsed, param);
			parsed = strtok((char *)0,"&");
		}
    	if(atoi(result) == 0){
    		utils.error("can not found the param ","UNKNOWN_PARAM", "i_GET", __LINE__);
    	}
    	va_end(arg);
    	return atoi(result);
    }
    catch(const char* error){
    	utils.error(error,"UNKNOWN ERROR", "i_GET", __LINE__);
    }
}
void Mw::Utils::error(const char* error,const char* href, const char* funct, int line){
	Mw::Template templ;
	char err_string[1025];
	sprintf(err_string,"<b>[Error]</b> : %s , Please check ",error);
	std::cout << "<table class=\"errors\" cellspacing=\"0\" summary=\"errors\">";
	std::cout << "<tr>";
	std::cout << "<td class=\"errorDept\" colspan=\"3\">Error : <b>" << funct << "</b> line " << line <<"</td>";
	std::cout << "</tr>";
	std::cout << "<td class=\"error\" width=\"25%\"><a href=\"" << href << "\">"<< href <<"</a></td>";
	std::cout << "<td class=\"error\" width=\"60%\">"<< error << "</td>";
	std::cout << "<td class=\"error\" width=\"15%\">"<< clock() <<"</td>";
	std::cout << "</tr>";
	std::cout << "</table>";
	exit(1);
	//templ.show_notif(err_string, href, href, ERROR);
	/* TODO : write logs */
}
void Mw::Methods::redirect(const char* href){
	//std::cout << "<META HTTP-EQUIV=refresh CONTENT=\"1;URL='" << href << "'\">\n";
	/* call header function */
	Mw::Function * funct = new Mw::Function;
	char * location = NULL;
	sprintf(location,"Location: %s",href);
	funct->header(location);

	return ;
}
/*
	Function: __end
	description: end of the web page
*/
void Mwu::Frame::end(){
	/* end page web */
	std::cout << "\t</body>\n</html>";
}
void Mw::Utils::die(const char* msg){
    std::cout << msg << std::endl;
    std::cerr << msg << std::endl;
    exit(1);
}
/*  
================================
		List function
================================
*/
list * Mw::List::sConstruct(){
	SmwList *l = NULL; /* initialisation of our list */
}
/*
	Function: p_sprint
	description: insert data to the end using head method , the first deta insered will be the last
*/
SmwList * Mw::List::p_sprint(SmwList *list, char c){
	SmwList * p_new; /* our new ptr */
	p_new = (SmwList *)malloc(sizeof(SmwList));
	p_new->c = c; /* add the data to the list */
	p_new->p_sv = list;

	return p_new;
}
/*
	Function: show
	description: show the list
*/
SmwList * Mw::List::show(SmwList *list){
	SmwList * p_tmp; /* tmp pointer */
	p_tmp = list; /* will point to our new adresse */
	for(p_tmp = list; p_tmp!=NULL;p_tmp=p_tmp->p_sv){
		std::cout << p_tmp->c;
	}

}