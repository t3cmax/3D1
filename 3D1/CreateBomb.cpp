#include "CreateBomb.h"

Group* CreateBomb()
{
	MatrixTransform *matrix_trans = new MatrixTransform();
	Matrix *matrix = new Matrix();
	Geode *node = new Geode();
	float radius = 10;

	//������ϸ�ȶ��󣬾�ϸ��Խ�ߣ�ϸ�־�Խ��
	osg::TessellationHints* hints = new osg::TessellationHints;
	//���þ�ϸ��Ϊ0.5f
	hints->setDetailRatio(0.5f);

	//���һ�����壬��һ��������Ԥ���弸������󣬵ڶ����Ǿ�ϸ�ȣ�Ĭ��Ϊ0
	node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 100, 300), radius),hints));

	matrix_trans->addChild(node);
	matrix_trans->setUpdateCallback(new BombCallback(Vec3(0,100,300)));
	//matrix_trans->setDataVariance(osg::Object::DYNAMIC);
	return matrix_trans;
}