#include "Scene.h"

SceneGroup::SceneGroup(Group* root)
{
	scene_root = root;
	Bomb* bomb = new Bomb(Vec3(0,100,300));
	bomb_list.push_back(bomb);
	scene_root->addChild(bomb);
}


SceneGroup::~SceneGroup(void)
{
}

void SceneGroup::Update()
{
	std::list<Bomb*>::iterator iter;
	for(iter = bomb_list.begin(); iter!=bomb_list.end();)
	{
		if(CollideWithScene(*iter))
		{
			remove_list.push(*iter);
			iter = bomb_list.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	while(!remove_list.empty())
	{
		Entity* now_node = remove_list.front();
		remove_list.pop();
		scene_root->removeChild(now_node);
	}
}

bool SceneGroup::CollideWithScene(Entity* something)
{
	Vec3 now_position = something->getPosition();
	Vec3 velocity = something->GetVelocity();

	osgUtil::IntersectVisitor ivXY; 
	osg::ref_ptr<osg::LineSegment> lineXY = new osg::LineSegment(now_position, now_position+velocity); 
	ivXY.addLineSegment(lineXY);
	GAME.main_camera->m_pHostViewer->getSceneData()->accept(ivXY) ;

	if(ivXY.hits())
		return true;
	return false;
}

void SceneGroup::AddNode( Node* node )
{
	scene_root->addChild(node);
}
