#include "Entity.h"


Entity::Entity()
{
	move = new Move();
	this->setUpdateCallback(move);
}

Entity::Entity(Vec3 velocity, Vec3 accel, Vec3 position)
{
	this->setPosition(position);
	move = new Move(velocity, accel);
	this->setUpdateCallback(move);
}

Entity::~Entity(void)
{
}
