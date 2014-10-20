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
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "mwutil.h"
#include "cgic-lib.h"
#include "ccgi.h"

#define DEFAULT "mwf/bootstrap.min.css"
#define ERROR 1
#define WARNNING 2
#define SUCCESS 3
#define INFO 4

/* const for time */

#define SECOND 5
#define MSECOND 6
#define MINUTES 7

#define print std::cout


/*  simple list structure */

typedef struct Mw_list{
	char c; 						/* this simple list will contain just caracters */
	struct Mw_list *p_sv; 			/*  next ptr */

}SmwList;
/* double list structure */ 
typedef struct d_mw_list{
	char * string; 					/* our list will contain string ex : <p>test</p> or <img src="" /> */
	struct d_mw_list *p_sv; 		/* next ptr */
	struct d_ml_list *p_sp; 		/* last ptr */

}DmwList;
/* structure for all list */
typedef struct a_list{
	size_t len; 					/* size of our list */
	struct a_list *p_head; 			/* ptr of the head of our list  */
	struct a_list *p_tail; 			/* ptr ot the end of our list */
}list;

namespace Mw{

	class Utils
	{
		public:
			int write(const char* string, ...);
			void error(const char* string,const char* ref);
			void die(const char* msg);
			
	};
	class List
	{
		public:
			/* function for list management */
			SmwList * s_init(SmwList *list);
			DmwList * d_init(DmwList **list);
			SmwList * s_del(SmwList *list);
			DmwList * d_del(DmwList **list);

			/*  list construct function */
			list * __sconstruct();
			list * __dconstruct();
		
			/* util function for list */
			int sprint(SmwList *list , char c);
			int dprint(DmwList **list, char * string);
			int sexec(SmwList *list);
			int dexec(DmwList **list);

			/* insert: using head method  */  
			SmwList * p_sprint(SmwList *list, char c);
			DmwList * p_dprint(DmwList **list , char * string);

			/*  show list for testing or debuging */
			SmwList * show(SmwList *list);

	};
	class Html
	{
		public:
			void link(const char* string, const char* href, const char* style);
			void p(const char* string, const char* style);
			void h(const char* string,int type, const char* style);
			void img(const char* src, int heigh, int width);
			void css_local(const char* file, const char* type);
			void div(const char* style);
			void span(const char *style);
			void ul(const char* style);
			void li(const char* style);
			void code(const char* string, const char* style);
			void js_local(const char* file);
			void css_web(const char* href, const char* type);
			void js_web(const char* href);
			void checkbox(char* string, const char* style);

	};
	class Methods
	{
		public:
			char * _GET(char* param);
			char * _POST(const char* param);
			int i_GET(char param[1025]);
			void redirect(const char* href);
	};
	class Time
	{
		public:
			clock_t load_page();
			clock_t load_composent();
			clock_t load_list(SmwList * list);
			clock_t currentTime();
			double loadedTime(clock_t start, clock_t end);
			void draw_time(clock_t start, clock_t end, int type);

	};
	class Template
	{
		public:
			void __load(const char* path);
			void write_code(const char* msg);
			void write_color(const char* msg, int color);
			void show_button(const char* msg, int style);
			void show_social_button(const char* msg, int type);
			void show_panel(const char* title, const char** content,const char* footer, int type);
			void show_notif(const char* content, const char* href_content, const char* href, int type);
			void errorStyle();

	};
	class Function
	{
		public:
			void removeChr(char *str, char c);
			void removeNbr(char *str);
			void getNbr(char *str);
			void removeStr(char* str, const char *r);
			char * parsing_url(char *s, char* param);
			int url_isset();
			int isset(char * mod);
	};

}
