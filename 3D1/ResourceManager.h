#pragma once
#include "osgheaders.h"
using namespace osg;

class ResourceManager
{
public:
	Texture2D* bomb_texture;

public:
	ResourceManager(void);
	~ResourceManager(void);
};

