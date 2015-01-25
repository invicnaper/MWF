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

void Mw::Function::removeChr(char *str, char c){
	char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != c) dst++;
    }
    *dst = '\0';
}
void Mw::Function::removeNbr(char *str){
	int i = 0, j = 0;
	for(i=0; str[i]!='\0'; ++i)
    {
        while (!((str[i]>='a'&&str[i]<='z') || (str[i]>='A'&&str[i]<='Z' || str[i]=='\0')))
        {
            for(j=i;str[j]!='\0';++j)
            {
                str[j]=str[j+1];
            }
            str[j]='\0';
        }
    }
}
void Mw::Function::removeStr(char* str, const char *r){
	while( str=strstr(str,r) )
    	memmove(str,str+strlen(r),1+strlen(str+strlen(r)));
}
char * Mw::Function::parsing_url(char *s, char* param)
{
	Mw::Utils utils;
	char *vname;
	char *val;
	char result[1025];
	int c, i =0;
	char buf[3];

	if(!s) {
		printf("X_ERR='Null phrase'\n");
		return NULL;
	}
	vname = s;
	while(*s && (*s != '=')) s++;
	if(!*s) {
		printf("X_ERR='Null assignment'\n");
		return NULL;
	}
	*(s++) = '\0';
	if(strcmp(vname, param) != 0){
		//utils.error("can not found the param ","UNKNOWN_PARAM");
	}
	for(val=s; *val; val++) {	
		switch( *val ) {
			case '%':
				buf[0]=*(++val); buf[1]=*(++val); 
				buf[2]='\0';
				sscanf(buf,"%2x",&c);
				break;
			case '+':
				c = ' ';
				break;
			default:
				c = *val;
		}
		if(strcmp(vname, param) == 0){
			result[i] = (char)c;
			i++;
		}
		/*
		switch(c) {
			case '\\': printf("\\\\"); break;
			case '\'': printf("\\'"); break;
			case '\n': printf("\\n"); break;
			default:   putchar((char)c); break;
		}
		*/
	}
	return result;
}
int Mw::Function::url_isset(){
	if(strcmp(getenv("QUERY_STRING"), "") == 0){
		return 0;
	}
	else{
		return 1;
	}
}
int Mw::Function::isset(char* mod){
	/* for _GET methode */
	if(strstr(getenv("QUERY_STRING"), mod)){
		return 1;
	}else{
		return 0;
	}
	/* for _POST methode */
}
void Mw::Function::header(char * string){
	/* must be called before any content drawing */
	Mw::Utils * utils = new Mw::Utils;
	try{
		std::cout << string << "\n\n";
	}catch(const char * error){
		utils->error(error,"Header error", "header", __LINE__);
	}
	return ;
}