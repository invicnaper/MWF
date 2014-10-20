# _   _  _ _ _  ___ 
#| \_/ || | | || __|
#| \_/ || V V || _| 
#|_| |_| \_n_/ |_| 
#this file will create the path and required files to build your web site

function help(){
	echo "%s  -h		: help"
	echo "%s  -simp 	: will create simple web plateform"
	echo "%s  -adv        : will create advanced web plateform(MVC)" 
}
function simple(){
	echo "creating folders"
	mkdir css	#folder for css files
	mkdir js	#folder for js files
	mkdir mwf	#folder for mwf files
	mkdir images	#folder for images files
	mkdir upload	#folder for upload files
	mkdir src 	#folder contain source code
	cp /usr/lib/mwf/Template/css/bootstrap.min.css mwf/ #copie the bootstrap cssfile
	cp /usr/lib/mwf/Examples/HelloWorld.cpp src/      #copie the cpp file
	cp /usr/lib/mwf/Examples/hello.mw ./ 		  #copie the index.mw
	mv hello.mw index.mw				  #rename the file	 	
	cp /usr/lib/wmf/Required/htaccess ./		  #copie the .htaccess file
	mv htaccess .htaccess	
		
}
function check_if_installed(){
	
	return 0
}
if [ "$1" == "-h" ]; then 
	help
fi

if [ "$1" == "-simp" ]; then
	simple
fi
