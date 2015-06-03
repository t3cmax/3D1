#include<iostream>

#include "osgheaders.h"

#include "cow.h"
#include "game.h"
#include "many_callback.h"
#include "constant.h"
#include "skybox.h"
#include "ManipulatorTravel.h"
#include "CreateLighting.h"
#include "TextureAndPrimitives.h"
#include "CreateBomb.h"
#include "SceneGroup.h"
#include "ResourceManager.h"
#include "CreateHUDText.h"

using namespace osg;

z_game GAME; 
ResourceManager *res_manager;



const int ReceivesShadowTraversalMask = 0x1;
const int CastsShadowTraversalMask = 0x2;
int main()
{
	osgViewer::Viewer* viewer = new osgViewer::Viewer();
	res_manager = new ResourceManager();

	Group* root = new Group() ;
	Group* scene_node = new Group();
	SceneGroup *scene_group = new SceneGroup(scene_node);

	//创建一个阴影节点，并标识接收对象和投影对象
	osgShadow::ShadowedScene* shadowedScene = new osgShadow::ShadowedScene();
	shadowedScene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
	shadowedScene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

	//创建阴影纹理
	osgShadow::ShadowTexture* st = new osgShadow::ShadowTexture();
	//关联阴影纹理
	shadowedScene->setShadowTechnique(st);

	Node* player_node = new osg::Node();
	Node* lz_node = new osg::Node();
	Node* enemy_node = new osg::Node();
	Node* fence_node[3];

	player_node = osgDB::readNodeFile("boy_run1.ive");
	player_node->setNodeMask(CastsShadowTraversalMask);

	lz_node = osgDB::readNodeFile("lz.osg");
	lz_node->setNodeMask(ReceivesShadowTraversalMask);

	osg::Image* wall_image = new osg::Image();
	wall_image = osgDB::readImageFile("wall.jpg");
	fence_node[0] = createWall(wall_image, -300, 300, 170);
	fence_node[1] = createWall(wall_image, -300, 300, 170);

	//创建矩阵变换节点
	MatrixTransform* mt = new osg::MatrixTransform();
	MatrixTransform* mt2 = new osg::MatrixTransform();
	MatrixTransform* fence_mt[4];

	scene_group->AddNode(mt);
	mt->addChild(player_node);
	scene_group->SetPlayerMatrixTrans(mt);

	scene_group->AddNode(mt2);
	mt2->addChild(lz_node);

	for(int i=1; i<=4; i++)
	{
		fence_mt[i] = new MatrixTransform();
		fence_mt[i]->addChild(fence_node[(i-1)/2]);
		Matrix fence_matrix;
		if(i==1)
		{
			fence_matrix.setTrans(Vec3(0,270,40));
		}
		else if(i==2)
		{
			fence_matrix.setTrans(Vec3(0, -280, -60));
		}
		else if(i==3)
		{
			fence_matrix.makeRotate(osg::PI/2, Vec3(0,0,1));
			fence_matrix.postMultTranslate(Vec3(250,0,30));
		}
		else if(i==4)
		{
			fence_matrix.makeRotate(-osg::PI/2, Vec3(0,0,1));
			fence_matrix.postMultTranslate(Vec3(-270,0,-60));
		}
		
		fence_mt[i]->setMatrix(fence_matrix);
		scene_group->AddNode(fence_mt[i]);
	}

	//得到相机
	Camera* camera = viewer->getCamera();

	//设置相机事件回调
	camera->setEventCallback(new z_camera_callback());
	mt->setUpdateCallback(new z_cow_callback());

	shadowedScene->addChild(scene_group->scene_root);
	Group* light_node = CreateLighting(scene_group->scene_root);
	shadowedScene->addChild(light_node);

	////////////////////////////////////////////////////////////////////////////
	
	root->addChild(createSkyBox());
	root->addChild(shadowedScene);
	root->addChild(createHUDText(scene_group->health));
	root->addChild(createHUDText(scene_group->score));

	//把漫游器加入到场景中
	GAME.main_camera=TravelManipulator::TravelToScene(viewer);

	//优化场景数据
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root);

	viewer->setSceneData(root);

	viewer->realize();

	bool already_over = false;
	while(!viewer->done())
	{
		scene_group->Update();
		if(!already_over && scene_group->GameOver())
		{
			osgText::Text* gameover_text = new osgText::Text();
			gameover_text->setText("Game Over\nPress ESC to Exit");
			gameover_text->setFont(res_manager->simhei);
			gameover_text->setPosition(Vec3(400, 500, 0));
			gameover_text->setColor(Vec4(1, 1, 1, 1));
			gameover_text->setCharacterSize(60.0);
			root->addChild(createHUDText(gameover_text));
			already_over = true;
		}
		viewer->frame();
	}

	return 0 ;
}