#include "Bomb.h"

Bomb::Bomb(void) : Entity( Vec3(0.1, 0, 0),Vec3(0, 0, -0.0002) )
{
	Geode *bomb_node = new Geode();
	float radius = 10;

	//������ϸ�ȶ��󣬾�ϸ��Խ�ߣ�ϸ�־�Խ��
	osg::TessellationHints* hints = new osg::TessellationHints;
	//���þ�ϸ��Ϊ0.5f
	hints->setDetailRatio(0.5f);

	//���һ�����壬��һ��������Ԥ���弸������󣬵ڶ����Ǿ�ϸ�ȣ�Ĭ��Ϊ0
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
