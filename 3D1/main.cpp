#include<iostream>
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osgGA/EventVisitor>

#include <osgUtil/Optimizer>

#include "cow.h"
#include "game.h"
#include "many_callback.h"
#include "constant.h"
#include "skybox.h"
#include "ManipulatorTravel.h"
#include "CreateLighting.h"

using namespace osg;
using namespace osgViewer;
using namespace std;

z_game GAME; 

int main()
{
	Viewer* viewer = new osgViewer::Viewer();

	Group* root = new osg::Group() ;

	Node* cow_node = new osg::Node();
	Node* lz_node = new osg::Node();
	Group* light_node = new osg::Group();

	cow_node = osgDB::readNodeFile("boy_run1.ive");
	lz_node = osgDB::readNodeFile("lz.osg");
	//创建矩阵变换节点
	MatrixTransform* mt = new osg::MatrixTransform();
	MatrixTransform* mt2 = new osg::MatrixTransform();

	light_node->addChild(mt);
	mt->addChild(cow_node);

	light_node->addChild(mt2);
	mt2->addChild(lz_node);
	mt2->addChild(createSkyBox());
	//设置更新回调
	

	//得到相机
	Camera* camera  = viewer->getCamera();

	//设置相机事件回调
	camera->setEventCallback(new z_camera_callback());
	mt->setUpdateCallback(new z_cow_callback());
	////////////////////////////////////////////////////////////////////////////
	Group* after_create = CreateLighting(light_node);
	root->addChild(after_create);

	//把漫游器加入到场景中
	GAME.main_camera=TravelManipulator::TravelToScene(viewer);


	//优化场景数据
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root);

	viewer->setSceneData(root);

	viewer->realize();

	viewer->run();

	return 0 ;
}