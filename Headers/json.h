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
#ifndef HJSON
#define HJSON
#include "mwf.h"

#define JSON_NONE 					0
#define JSON_HEX_QUOT 				1
#define JSON_HEX_TAG				2
#define JSON_HEX_AMP				3
#define JSON_HEX_APOS				4
#define JSON_NUMERIC_CHECK			5
#define JSON_PRETTY_PRINT			6
#define JSON_UNESCAPED_SLASHES		7
#define JSON_FORCE_OBJECT			8
#define JSON_UNESCAPED_UNICODE		9


/* json struct */

typedef struct sJson{
	char ** data; 					/* array of strings */
	int option;
}json;

namespace Json{}

	class Function{
		public:
			json encode(char ** data);
			char ** decode(json j);
	};

	class File{
		public:
			void parse(char * path);
	};
}
#endif