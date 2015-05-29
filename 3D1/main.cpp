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

	//创建一个阴影节点，并标识接收对象和投影对象
	osgShadow::ShadowedScene* shadowedScene = new osgShadow::ShadowedScene();
	shadowedScene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
	shadowedScene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

	//创建阴影纹理
	osgShadow::ShadowTexture* st = new osgShadow::ShadowTexture();
	//关联阴影纹理
	shadowedScene->setShadowTechnique(st);

	Node* cow_node = new osg::Node();
	Node* lz_node = new osg::Node();
	Group* scene_node = new osg::Group();

	cow_node = osgDB::readNodeFile("boy_run1.ive");
	cow_node->setNodeMask(CastsShadowTraversalMask);

	lz_node = osgDB::readNodeFile("lz.osg");
	lz_node->setNodeMask(ReceivesShadowTraversalMask);
	//创建矩阵变换节点
	MatrixTransform* mt = new osg::MatrixTransform();
	MatrixTransform* mt2 = new osg::MatrixTransform();

	scene_node->addChild(mt);
	mt->addChild(cow_node);

	scene_node->addChild(mt2);
	mt2->addChild(lz_node);

	//得到相机
	Camera* camera = viewer->getCamera();

	//设置相机事件回调
	camera->setEventCallback(new z_camera_callback());
	mt->setUpdateCallback(new z_cow_callback());

	shadowedScene->addChild(scene_node);
	Group* light_node = CreateLighting(scene_node);
	shadowedScene->addChild(light_node);

	////////////////////////////////////////////////////////////////////////////
	
	root->addChild(createSkyBox());
	root->addChild(shadowedScene);

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