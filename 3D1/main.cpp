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

#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowVolume>
#include <osgShadow/ShadowTexture>
#include <osgShadow/ShadowMap>
#include <osgShadow/SoftShadowMap>
#include <osgShadow/ParallelSplitShadowMap>

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

const int ReceivesShadowTraversalMask = 0x1;
const int CastsShadowTraversalMask = 0x2;

int main()
{
	Viewer* viewer = new osgViewer::Viewer();
	Group* root = new osg::Group() ;

	//����һ����Ӱ�ڵ㣬����ʶ���ն����ͶӰ����
	osgShadow::ShadowedScene* shadowedScene = new osgShadow::ShadowedScene();
	shadowedScene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
	shadowedScene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

	//������Ӱ����
	osgShadow::ShadowTexture* st = new osgShadow::ShadowTexture();
	//������Ӱ����
	shadowedScene->setShadowTechnique(st);

	Node* cow_node = new osg::Node();
	Node* lz_node = new osg::Node();
	Group* scene_node = new osg::Group();

	cow_node = osgDB::readNodeFile("boy_run1.ive");
	cow_node->setNodeMask(CastsShadowTraversalMask);

	lz_node = osgDB::readNodeFile("lz.osg");
	lz_node->setNodeMask(ReceivesShadowTraversalMask);
	//��������任�ڵ�
	MatrixTransform* mt = new osg::MatrixTransform();
	MatrixTransform* mt2 = new osg::MatrixTransform();

	scene_node->addChild(mt);
	mt->addChild(cow_node);

	scene_node->addChild(mt2);
	mt2->addChild(lz_node);

	//�õ����
	Camera* camera = viewer->getCamera();

	//��������¼��ص�
	camera->setEventCallback(new z_camera_callback());
	mt->setUpdateCallback(new z_cow_callback());

	shadowedScene->addChild(scene_node);
	Group* light_node = CreateLighting(scene_node);
	shadowedScene->addChild(light_node);

	////////////////////////////////////////////////////////////////////////////
	
	root->addChild(createSkyBox());
	root->addChild(shadowedScene);

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