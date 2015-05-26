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
	cow_node = osgDB::readNodeFile("boy_run1.ive");
	lz_node = osgDB::readNodeFile("lz.osg");
	//��������任�ڵ�
	MatrixTransform* mt = new osg::MatrixTransform();
	MatrixTransform* mt2 = new osg::MatrixTransform();
	mt->addChild(cow_node);
	root->addChild(mt2);
	mt2->addChild(lz_node);
	//���ø��»ص�
	

	//�õ����
	Camera* camera  = viewer->getCamera();

	//��������¼��ص�
	camera->setEventCallback(new z_camera_callback());
	mt->setUpdateCallback(new z_cow_callback());
	////////////////////////////////////////////////////////////////////////////

	root->addChild(mt);
	mt2->addChild(createSkyBox());


	//�����������뵽������
	GAME.main_camera=TravelManipulator::TravelToScene(viewer);


	//�Ż���������
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root);

	viewer->setSceneData(root);

	viewer->realize();

	viewer->run();

	return 0 ;
}