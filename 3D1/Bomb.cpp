#include "Bomb.h"

Bomb::Bomb(void) : Entity( Vec3(0.1, 0, 0), Vec3(0, 0, -0.001) , Vec3(0,0,0))
{
	CreateBomb();
}

Bomb::Bomb(Vec3 position, Vec3 speed) : Entity( speed, Vec3(0, 0, -0.001), position )
{
	CreateBomb();
}


Bomb::~Bomb(void)
{
}

void Bomb::CreateBomb()	
{
	Geode *bomb_node = new Geode();
	float radius = 10;

	//创建精细度对象，精细度越高，细分就越多
	osg::TessellationHints* hints = new osg::TessellationHints;
	//设置精细度为0.5f
	hints->setDetailRatio(0.5f);

	//添加一个球体，第一个参数是预定义几何体对象，第二个是精细度，默认为0
	bomb_node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(Vec3(0, 0, 0), radius),hints));
	this->addChild(bomb_node);
}