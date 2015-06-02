#pragma once
#include "osgheaders.h"
using namespace osg;

class Move : public NodeCallback
{
private: 
	Vec3 velocity;
	Vec3 accel; 

public:
	Move();
	Move(Vec3 v, Vec3 a);
	virtual void operator() (osg::Node*, osg::NodeVisitor*);

	Vec3 getVelocity();
	Vec3 getAccel();

};