#pragma once
#include "osgheaders.h"
#include <list>
#include <queue>
#include "Entity.h"
#include "Bomb.h"
#include "constant.h"
using namespace osg;

class SceneGroup
{
public:
	Group* scene_root;

	std::queue<Entity*> add_list;
	std::queue<Entity*> remove_list;

	std::list<Bomb*> bomb_list;
public:
	SceneGroup(Group* root);
	~SceneGroup(void);
	void Update();
	bool CollideWithScene(Entity* something);

	void AddNode(Node* node);
};

