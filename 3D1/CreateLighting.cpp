#include "CreateLighting.h"

//向场景中添加光源
osg::Group* CreateLighting(osg::Node* node)
{
	osg::Group* lightRoot= new osg::Group();
	lightRoot->addChild(node);

	//计算包围盒
	osg::BoundingSphere bs ;
	node->computeBound() ;
	bs=node->getBound() ;

	//开启光照
	osg::StateSet* stateset = new osg::StateSet();
	stateset = lightRoot->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHT0,osg::StateAttribute::ON);
	//stateset->setMode(GL_LIGHT1, osg::StateAttribute::ON);

	//创建一个Light对象
	osg::Light* light = new osg::Light();
	light->setLightNum(1);
	
	//using namespace std;
	//cout<<"centerx: "<<bs.center().x()<<" centery: "<<bs.center().y()<<" centerz: "<<bs.center().z()<<endl;


	//设置位置
	light->setPosition(osg::Vec4(bs.center().x(), bs.center().y(), bs.center().z()+bs.radius(), 1.0f));
	//设置环境光的颜色
	light->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//设置散射光的颜色
	light->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	//创建光源
	osg::LightSource* lightSource = new osg::LightSource();
	lightSource->setLight(light);

	lightRoot->addChild(lightSource);

	return lightRoot ;

	/*osg::ComputeBoundsVisitor cbbv;
	node->accept(cbbv);
	osg::BoundingBox bb = cbbv.getBoundingBox();

	osg::Vec4 lightpos;

	lightpos.set(bb.center().x(), bb.center().y(), bb.zMax() + bb.radius()*2.0f  ,1.0f);

	osg::LightSource* ls = new osg::LightSource();
	ls->getLight()->setPosition(lightpos);

	ls->getLight()->setAmbient(osg::Vec4(0.2,0.2,0.2,1.0));
	ls->getLight()->setDiffuse(osg::Vec4(0.8,0.8,0.8,1.0));

	return ls;*/
}
