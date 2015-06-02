#pragma once
#include "osgheaders.h"
#include "Move.h"
using namespace osg;

class Entity : public PositionAttitudeTransform
{
private: 
	Move* move;
public:
	Entity();
	Entity(Vec3 velocity, Vec3 accel, Vec3 position);
	Vec3 GetVelocity(){return move->getVelocity();}
	~Entity();
};


