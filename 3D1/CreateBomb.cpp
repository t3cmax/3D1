#include "CreateBomb.h"

Group* CreateBomb()
{
	MatrixTransform *matrix_trans = new MatrixTransform();
	Matrix *matrix = new Matrix();
	Geode *node = new Geode();
	float radius = 10;

	//创建精细度对象，精细度越高，细分就越多
	osg::TessellationHints* hints = new osg::TessellationHints;
	//设置精细度为0.5f
	hints->setDetailRatio(0.5f);

	//添加一个球体，第一个参数是预定义几何体对象，第二个是精细度，默认为0
	node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 100, 300), radius),hints));

	matrix_trans->addChild(node);
	matrix_trans->setUpdateCallback(new BombCallback(Vec3(0,100,300)));
	//matrix_trans->setDataVariance(osg::Object::DYNAMIC);
	return matrix_trans;
}