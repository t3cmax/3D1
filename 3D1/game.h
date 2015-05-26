#ifndef _GAME_H_ 
#define _GAME_H_ 

#include "cow.h"
#include "ManipulatorTravel.h"

class z_game
{
    public:
		//int state;
		TravelManipulator* main_camera;
		z_cow cow;

		z_game();
		~z_game();
};



#endif 