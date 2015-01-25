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

clock_t Mw::Time::load_page(){
	/* time of execution */
	clock_t current_time = clock();

	return current_time;
}
clock_t Mw::Time::currentTime(){
	clock_t my_time = clock();

	return my_time;
}
double Mw::Time::loadedTime(clock_t start, clock_t end){
	double loaded = (double)(end - start)/CLOCKS_PER_SEC;

	return loaded;
}
void Mw::Time::draw_time(clock_t start, clock_t end, int type){
	switch(type){
		case SECOND:
			printf("%.6fs", (double)(end - start)/CLOCKS_PER_SEC);
			break;
		case MSECOND:
			printf("%.6fs", (double)(end - start));
			break;
	}

	return;
}