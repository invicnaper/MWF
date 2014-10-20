![alt text](https://cdn3.iconfinder.com/data/icons/internet-and-web-4/78/internt_web_technology-06-128.png "mwf logo")

MWF
===

MWF is a web framework written in C++

Source code
===

Download the source code and than build them using :

    $make compil
  
Code Example
===

### Param :
    #include "mwf.h"
    int main(){
        Mwu::Frame frame;
        Mw::Html html;
        Mw::Methods m;
        Mw::Function funct;
        int a ;
        frame.__init("Param testing","Description");
        if(funct.url_isset()){
                a = m.i_GET("a");
                print << "a = " << a ; 
        }else{
                print << "<b>no param</b>";
        }
        frame.__end();
        return 0;
    }
this will check if the query string exist and then will print the content of the param "a"

Mwf lib 
===

### Linux :
you can download the .deb package or the mwf installer in [libmwflin](https://www.naper.eu)

### Windows :
soon

Documentation
===

##Mwu::Frame

    void 	__init (const char *title, const char *description)
    void 	__load (const char *module)
    void 	__end ()

##Mw::List

    SmwList * 	s_init (SmwList *list)
    DmwList * 	d_init (DmwList **list)
    SmwList * 	s_del (SmwList *list)
    DmwList * 	d_del (DmwList **list)
    list * 	__sconstruct ()
    list * 	__dconstruct ()
    int 	sprint (SmwList *list, char c)
    int 	dprint (DmwList **list, char *string)
    int 	sexec (SmwList *list)
    int 	dexec (DmwList **list)
    SmwList * 	p_sprint (SmwList *list, char c)
    DmwList * 	p_dprint (DmwList **list, char *string)
    SmwList * 	show (SmwList *list)
