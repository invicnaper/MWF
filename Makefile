# _   _  _ _ _  ___ 
#| \_/ || | | || __|
#| \_/ || V V || _| 
#|_| |_| \_n_/ |_|  
#
#@author : naper
#@description : c++ web framework
#Filename: Makefile
OBJ=help
BINDIR=obj
WININSTDIR=install
ARCHDIR=targz

all: $(OBJ)

help:
	@echo  '**************************************'	
	@echo  '*  MWF lib Building    *'
	@echo  '**************************************'
	@echo
	@echo  'make compil 		: Build libmwf'
	@echo  'make compil-c++11   : using std c++ 11'
	@echo  'make link 	        : linking libmwf'

compil: compilmsg
compilmsg:
	@echo ===================[Compiling MWF]===================
	gcc -c Frame/mwf.cpp -o mwf.o
	gcc -c Utils/utils.cpp -o utils.o
	gcc -c Template/template.cpp -o template.o 
	gcc -c Utils/time.cpp -o time.o
	gcc -c Utils/function.cpp -o function.o 
	gcc -c Utils/ccgi.cpp -o libcgi.o
	#gcc -c Utils/cgic-lib.cpp -o cgi.o
	@echo ===================[Finished]===================
compil-c++11:
compil-c++11msg:
	gcc -c Frame/mwf.cpp -o mwf.o -std=c++11
	gcc -c Utils/utils.cpp -o utils.o -std=c++11
	gcc -c Template/template.cpp -o template.o -std=c++11
	gcc -c Utils/time.cpp -o time.o -std=c++11
	gcc -c Utils/function.cpp -o function.o -std=c++11
	#gcc -c Utils/cgic-lib.cpp -o cgi.o
	@echo ===================[Finished]===================
link: linkmsg
linkmsg:
	@echo ===================[Compiling MWF]===================
	ar -q libmwflin.a mwf.o utils.o template.o time.o cgi.o function.o libcgi.o
	@echo ===================[Finished]===================
