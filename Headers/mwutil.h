/*
 _   _  _ _ _  ___ 
| \_/ || | | || __|
| \_/ || V V || _| 
|_| |_| \_n_/ |_|  

@author : naper
@description : c++ web framework

*/
namespace Mwu{

	class Frame
	{
		public:
			void init(const char* title,const char* description);
			void fload(const char *module);
			void end();
			Frame(const char* title, const char * descr);
			~Frame();
		private:
			const char * cDescription;
			const char * cTitle;
	};

}