#include <mwf.h>


int main(){
	Mw::Html html; 		 /* init html  */
	Mwu::Frame frame;	 /* init frame */

	frame.__init("MWF","description");
	
	html.p("Hello world",NULL);
	
	frame.__end();	

	return 0;
}
