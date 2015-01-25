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
	g++ -c Frame/mwf.cpp -o mwf.o
	g++ -c Utils/mwf_utils.cpp -o utils.o
	g++ -c Template/mwf_template.cpp -o template.o 
	g++ -c Utils/mwf_time.cpp -o time.o
	g++ -c Utils/mwf_function.cpp -o function.o 
	g++ -c Utils/ccgi.cpp -o libcgi.o
	#gcc -c Utils/cgic-lib.cpp -o cgi.o
	@echo ===================[Finished]===================
compil-c++11:
compil-c++11msg:
	g++ -c Frame/mwf.cpp -o mwf.o -std=c++11
	g++ -c Utils/utils.cpp -o utils.o -std=c++11
	g++ -c Template/template.cpp -o template.o -std=c++11
	g++ -c Utils/time.cpp -o time.o -std=c++11
	g++ -c Utils/function.cpp -o function.o -std=c++11
	#gcc -c Utils/cgic-lib.cpp -o cgi.o
	@echo ===================[Finished]===================
link: linkmsg
linkmsg:
	@echo ===================[Compiling MWF]===================
	#add cgi.o if you have it :p
	ar -q libmwflin.a mwf.o utils.o template.o time.o function.o libcgi.o
	@echo ===================[Finished]===================
