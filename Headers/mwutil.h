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
			void __init(const char* title,const char* description);
			void __load(const char *module);
			void __end();
	};

}