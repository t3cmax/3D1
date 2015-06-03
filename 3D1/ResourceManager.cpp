#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
	Image* image = osgDB::readImageFile("moon_texture2.jpg");
	bomb_texture = new Texture2D(image);
	simhei = osgText::readFontFile("simhei.ttf");
}


ResourceManager::~ResourceManager(void)
{
}
