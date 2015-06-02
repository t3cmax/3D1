#include "TextureAndPrimitives.h"

osg::Node* createWall(osg::Image* image, float start_x, float end_x, float height)
{
	//�����ı���
	osg::Geometry* geometry = new osg::Geometry() ;

	//���ö���
	osg::Vec3Array* v = new osg::Vec3Array();
	v->push_back(osg::Vec3(start_x, 0.0, 0)) ;
	v->push_back(osg::Vec3(end_x, 0.0, 0)) ;
	v->push_back(osg::Vec3(end_x, 0.0, height)) ;
	v->push_back(osg::Vec3(start_x, 0.0, height)) ;

	geometry->setVertexArray(v) ;

	//���÷���
	osg::Vec3Array* normal = new osg::Vec3Array() ;
	normal->push_back((osg::Vec3(-1.0f,0.0f,0.0f)^osg::Vec3(0.0f,0.0f,1.0f)));

	geometry->setNormalArray(normal) ;
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL) ;

	//������������
	osg::Vec2Array* vt = new osg::Vec2Array() ;
	vt->push_back(osg::Vec2(0.0f,0.0f)) ;
	vt->push_back(osg::Vec2(1.0f,0.0f)) ;
	vt->push_back(osg::Vec2(1.0f,1.0f)) ;
	vt->push_back(osg::Vec2(0.0f,1.0f)) ;

	geometry->setTexCoordArray(0,vt) ;

	//�����ı���
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4)) ;

	if(image)
	{
		//״̬���Զ���
		osg::StateSet* stateset = new osg::StateSet() ;

		//����һ��Texture2D���Զ���
		osg::Texture2D* texture = new osg::Texture2D() ;
		//����image
		texture->setImage(image) ;
		//����Texture2D������󣬵���������Ĭ��ΪON
		stateset->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON) ;
		//���û��
		stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
		//�رչ���
		stateset ->setMode (GL_LIGHTING, osg::StateAttribute ::OFF) ;

		geometry->setStateSet(stateset) ;
	}
	osg::Geode *node = new osg::Geode();
	node->addDrawable(geometry);

	return node;

}