#include "TextureAndPrimitives.h"

osg::Node* createWall(osg::Image* image, float start_x, float end_x, float height)
{
	//创建四边形
	osg::Geometry* geometry = new osg::Geometry() ;

	//设置顶点
	osg::Vec3Array* v = new osg::Vec3Array();
	v->push_back(osg::Vec3(start_x, 0.0, 0)) ;
	v->push_back(osg::Vec3(end_x, 0.0, 0)) ;
	v->push_back(osg::Vec3(end_x, 0.0, height)) ;
	v->push_back(osg::Vec3(start_x, 0.0, height)) ;

	geometry->setVertexArray(v) ;

	//设置法线
	osg::Vec3Array* normal = new osg::Vec3Array() ;
	normal->push_back((osg::Vec3(-1.0f,0.0f,0.0f)^osg::Vec3(0.0f,0.0f,1.0f)));

	geometry->setNormalArray(normal) ;
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL) ;

	//设置纹理坐标
	osg::Vec2Array* vt = new osg::Vec2Array() ;
	vt->push_back(osg::Vec2(0.0f,0.0f)) ;
	vt->push_back(osg::Vec2(1.0f,0.0f)) ;
	vt->push_back(osg::Vec2(1.0f,1.0f)) ;
	vt->push_back(osg::Vec2(0.0f,1.0f)) ;

	geometry->setTexCoordArray(0,vt) ;

	//绘制四边形
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4)) ;

	if(image)
	{
		//状态属性对象
		osg::StateSet* stateset = new osg::StateSet() ;

		//创建一个Texture2D属性对象
		osg::Texture2D* texture = new osg::Texture2D() ;
		//关联image
		texture->setImage(image) ;
		//关联Texture2D纹理对象，第三个参数默认为ON
		stateset->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON) ;
		//启用混合
		stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
		//关闭光照
		stateset ->setMode (GL_LIGHTING, osg::StateAttribute ::OFF) ;

		geometry->setStateSet(stateset) ;
	}
	osg::Geode *node = new osg::Geode();
	node->addDrawable(geometry);

	return node;

}