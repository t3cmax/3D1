#ifndef _COW_H_ 
#define _COW_H_ 



class z_cow
{
    public:
		int state;//1,2,4,8,16,32��Ӧǰ�������ң�����������
		bool inited;
		double dir;
		double speed;
		double angle_f;

		bool hurt;
		z_cow();
		~z_cow();
};



#endif 