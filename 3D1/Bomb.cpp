#include "Bomb.h"

Bomb::Bomb(void) : Entity( Vec3(0.1, 0, 0),Vec3(0, 0, -0.0002) )
{
	Geode *bomb_node = new Geode();
	float radius = 10;

	//创建精细度对象，精细度越高，细分就越多
	osg::TessellationHints* hints = new osg::TessellationHints;
	//设置精细度为0.5f
	hints->setDetailRatio(0.5f);

	//添加一个球体，第一个参数是预定义几何体对象，第二个是精细度，默认为0
	bomb_node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 100, 300), radius),hints));
	this->addChild(bomb_node);

}

Bomb::Bomb(Vec3 position) : Entity( Vec3(0.1, 0, 0), Vec3(0, 0, -0.0002) )
{
	Geode *bomb_node = new Geode();
	float radius = 10;

	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);

	bomb_node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(position, radius),hints));
	this->addChild(bomb_node);
}


Bomb::~Bomb(void)
{
}
