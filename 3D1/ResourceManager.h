#pragma once
#include "osgheaders.h"
using namespace osg;

class ResourceManager
{
public:
	Texture2D* bomb_texture;
	osgText::Font* simhei;

public:
	ResourceManager(void);
	~ResourceManager(void);
};

