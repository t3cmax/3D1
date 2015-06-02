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

	//������ϸ�ȶ��󣬾�ϸ��Խ�ߣ�ϸ�־�Խ��
	osg::TessellationHints* hints = new osg::TessellationHints;
	//���þ�ϸ��Ϊ0.5f
	hints->setDetailRatio(0.5f);

	//���һ�����壬��һ��������Ԥ���弸������󣬵ڶ����Ǿ�ϸ�ȣ�Ĭ��Ϊ0
	bomb_node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(Vec3(0, 0, 0), radius),hints));
	this->addChild(bomb_node);
}