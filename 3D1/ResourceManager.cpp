#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
	Image* image = osgDB::readImageFile("moon_texture2.jpg");
	bomb_texture = new Texture2D(image);
}


ResourceManager::~ResourceManager(void)
{
}
