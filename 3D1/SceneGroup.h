#pragma once
#include "osgheaders.h"
#include <list>
#include <queue>
#include "Entity.h"
#include "Bomb.h"
#include "constant.h"
#include "ResourceManager.h"
using namespace osg;

class SceneGroup
{
public:
	Group* scene_root;

	std::queue<Entity*> add_list;
	std::queue<Entity*> remove_list;

	std::list<Bomb*> bomb_list;

	unsigned int cnt ;

	MatrixTransform *player_matrix;

	osg::ref_ptr<osg::Program> program_normal;
	osg::ref_ptr<osg::Program> program_red;
	int hurt_cnt;
	bool hurt;

public:
	SceneGroup(Group* root);
	~SceneGroup(void);
	void Update();
	bool CollideWithScene(Entity* something);
	bool CollideWithPlayer(Entity* something);

	void AddNode(Node* node);
	void AddBomb(Vec3 position, Vec3 speed);
	void SetPlayerMatrixTrans(MatrixTransform *p_matrix);
};

