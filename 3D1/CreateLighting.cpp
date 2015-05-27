#include "CreateLighting.h"

//向场景中添加光源
osg::Group* CreateLighting(osg::Node* node)
{
	osg::Group* lightRoot= new osg::Group();
	lightRoot->addChild(node);

	//开启光照
	osg::StateSet* stateset = new osg::StateSet();
	stateset = lightRoot->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHT0,osg::StateAttribute::ON);

	//计算包围盒
	osg::BoundingSphere bs ;
	node->computeBound() ;
	bs=node->getBound() ;

	//创建一个Light对象
	osg::Light* light = new osg::Light();
	light->setLightNum(0);
	//设置方向
	light->setDirection(osg::Vec3(0.0f,0.0f,-1.0f));
	//设置位置
	light->setPosition(osg::Vec4(bs.center().x(),bs.center().y(),bs.center().z()+bs.radius(),0.0f));
	//设置环境光的颜色
	light->setAmbient(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
	//设置散射光的颜色
	light->setDiffuse(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

	//设置恒衰减指数
	light->setConstantAttenuation(1.0f);
	//设置线形衰减指数
	light->setLinearAttenuation(0.0f);
	//设置二次方衰减指数
	light->setQuadraticAttenuation(0.0f);

	//创建光源
	osg::LightSource* lightSource = new osg::LightSource();
	lightSource->setLight(light);

	lightRoot->addChild(lightSource);

	return lightRoot ;
}
