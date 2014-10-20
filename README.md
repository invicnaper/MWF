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
```c++
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
```
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

##Mw::Html

    void 	link (const char *string, const char *href, const char *style)
    void 	p (const char *string, const char *style)
    void 	h (const char *string, int type, const char *style)
    void 	img (const char *src, int heigh, int width)
    void 	css_local (const char *file, const char *type)
    void 	div (const char *style)
    void 	span (const char *style)
    void 	ul (const char *style)
    void 	li (const char *style)
    void 	code (const char *string, const char *style)
    void 	js_local (const char *file)
    void 	css_web (const char *href, const char *type)
    void 	js_web (const char *href)
    void 	checkbox (char *string, const char *style)
    
##Mw::Methods

    char * 	_GET (char *param)
    char * 	_POST (const char *param)
    int 	i_GET (char param[1025])
    void 	redirect (const char *href)
    
##Mw::Time
    
    clock_t 	load_page ()
    clock_t 	load_composent ()
    clock_t 	load_list (SmwList *list)
    clock_t 	currentTime ()
    double 	loadedTime (clock_t start, clock_t end)
    void 	draw_time (clock_t start, clock_t end, int type)

##Mw::Function

    void 	removeChr (char *str, char c)
    void 	removeNbr (char *str)
    void 	getNbr (char *str)
    void 	removeStr (char *str, const char *r)
    char * 	parsing_url (char *s, char *param)
    int 	url_isset ()
    int 	isset (char *mod)
