#pragma once
#include "osgheaders.h"
#include "Entity.h"
using namespace osg;


class Bomb : public Entity
{
public:

public:
	Bomb(void);
	Bomb(Vec3 position);
	~Bomb(void);
};

