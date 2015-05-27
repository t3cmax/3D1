#include "CreateLighting.h"

//�򳡾�����ӹ�Դ
osg::Group* CreateLighting(osg::Node* node)
{
	osg::Group* lightRoot= new osg::Group();
	lightRoot->addChild(node);

	//��������
	osg::StateSet* stateset = new osg::StateSet();
	stateset = lightRoot->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHT0,osg::StateAttribute::ON);

	//�����Χ��
	osg::BoundingSphere bs ;
	node->computeBound() ;
	bs=node->getBound() ;

	//����һ��Light����
	osg::Light* light = new osg::Light();
	light->setLightNum(0);
	//���÷���
	light->setDirection(osg::Vec3(0.0f,0.0f,-1.0f));
	//����λ��
	light->setPosition(osg::Vec4(bs.center().x(),bs.center().y(),bs.center().z()+bs.radius(),0.0f));
	//���û��������ɫ
	light->setAmbient(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
	//����ɢ������ɫ
	light->setDiffuse(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

	//���ú�˥��ָ��
	light->setConstantAttenuation(1.0f);
	//��������˥��ָ��
	light->setLinearAttenuation(0.0f);
	//���ö��η�˥��ָ��
	light->setQuadraticAttenuation(0.0f);

	//������Դ
	osg::LightSource* lightSource = new osg::LightSource();
	lightSource->setLight(light);

	lightRoot->addChild(lightSource);

	return lightRoot ;
}
