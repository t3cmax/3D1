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
	cow_node = osgDB::readNodeFile("cow.osg");
	lz_node = osgDB::readNodeFile("lz.osg");
	//创建矩阵变换节点
	MatrixTransform* mt = new osg::MatrixTransform();
	mt->addChild(cow_node);
	root->addChild(lz_node);
	//设置更新回调
	

	//得到相机
	Camera* camera  = viewer->getCamera();

	//设置相机事件回调
	camera->setEventCallback(new z_camera_callback());
	mt->setUpdateCallback(new z_cow_callback());
	////////////////////////////////////////////////////////////////////////////

	root->addChild(mt);
	mt->addChild(createSkyBox());

	//优化场景数据
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root);

	viewer->setSceneData(root);

	viewer->realize();

	viewer->run();

	return 0 ;
}