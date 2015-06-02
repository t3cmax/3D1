#include "Move.h"


Move::Move()
{
	velocity.set(Vec3(0,0,0));
	accel.set(Vec3(0,0,0));
}
Move::Move(Vec3 v, Vec3 a)
{
	velocity.set(v);
	accel.set(a);
}

void Move::operator() (osg::Node* n, osg::NodeVisitor* nv)
{
	PositionAttitudeTransform *node = dynamic_cast<PositionAttitudeTransform*>(n);

	velocity = velocity + accel;

	node->setPosition(node->getPosition() + velocity);

	traverse(n,nv);
}

osg::Vec3 Move::getVelocity()
{
	return velocity;
}

osg::Vec3 Move::getAccel()
{
	return accel;
}
