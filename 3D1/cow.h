#ifndef _COW_H_ 
#define _COW_H_ 



class z_cow
{
    public:
		int state;//1,2,4,8,16,32对应前，后，左，右，上，下
		bool inited;
		z_cow();
		~z_cow();
};



#endif 