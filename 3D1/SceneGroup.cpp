#include "SceneGroup.h"

SceneGroup::SceneGroup(Group* root)
{
	srand(time(0));
	scene_root = root;
	cnt=0;
	hurt_cnt=0;
	hurt = false;

	program_normal = new osg::Program();
	program_red = new osg::Program();
	program_red->addShader(osg::Shader::readShaderFile(osg::Shader::Type::VERTEX, "vertexshader.glsl"));

}


SceneGroup::~SceneGroup(void)
{
}

float RandomFloat(float from, float to)
{
	float tmp = float(rand())/RAND_MAX;
	tmp = (to-from) * tmp;
	return from+tmp;
}

Vec3 RandomVec3(Vec3 start, Vec3 end)
{
	float x = RandomFloat(start.x(), end.x());
	float y = RandomFloat(start.y(), end.y());
	float z = RandomFloat(start.z(), end.z());

	return Vec3(x,y,z);
}

void SceneGroup::Update()
{
	cnt++;
	if(cnt%25==0)
	{
		Vec3 start_pos = RandomVec3(Vec3(-220, -220, 250), Vec3(220, 220, 280));
		Vec3 start_speed = RandomVec3(Vec3(-0.2, -0.2, 0), Vec3(0.2, 0.2, 0));
		AddBomb(start_pos, start_speed);

		if(cnt%50==0)
		{
			Vec3 player_pos = Vec3(0,0,0) * player_matrix->getMatrix() + Vec3(0,0,250);
			AddBomb(player_pos, Vec3(0,0,0));
		}
	}

	std::list<Bomb*>::iterator iter;
	for(iter = bomb_list.begin(); iter!=bomb_list.end();)
	{
		if(CollideWithScene(*iter))
		{
			if(CollideWithPlayer(*iter))
			{
				hurt_cnt = 60;
			}
			remove_list.push(*iter);
			iter = bomb_list.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	if(hurt_cnt > 0 && hurt==false)
	{
		hurt = true;
		player_matrix->getOrCreateStateSet()->setAttributeAndModes(program_red, StateAttribute::Values::ON);
	}
	else if(hurt_cnt == 0 && hurt == true)
	{
		hurt = false;
		player_matrix->getOrCreateStateSet()->setAttributeAndModes(program_normal, StateAttribute::Values::ON);
	}

	if(hurt_cnt > 0)
		hurt_cnt--;

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

	//std::cout<<now_position.x()<<" "<<now_position.y()<<" "<<now_position.z()<<" "<<"\n";

	osgUtil::IntersectVisitor ivXY;
	osg::ref_ptr<osg::LineSegment> line[3];
	line[0] = new osg::LineSegment(now_position-Vec3(0, 0, 1), now_position+Vec3(0, 0, 1)); 
	line[1] = new osg::LineSegment(now_position-Vec3(0, 1, 0), now_position+Vec3(0, 1, 0));
	line[2] = new osg::LineSegment(now_position-Vec3(1, 0, 0), now_position+Vec3(1, 0, 0));

	for(int i=0; i<3; i++)
	{
		ivXY.addLineSegment(line[i]);
	}
	GAME.main_camera->m_pHostViewer->getSceneData()->accept(ivXY) ;

	if(ivXY.hits())
	{
		return true;
	}
	return false;
}

void SceneGroup::AddNode( Node* node )
{
	scene_root->addChild(node);
}

void SceneGroup::AddBomb( Vec3 position, Vec3 speed )
{
	Bomb* bomb = new Bomb(position, speed);
	bomb_list.push_back(bomb);
	scene_root->addChild(bomb);
	return;
}

void SceneGroup::SetPlayerMatrixTrans( MatrixTransform *p_matrix )
{
	player_matrix = p_matrix;
}

bool SceneGroup::CollideWithPlayer( Entity* something )
{
	Vec3 now_position = something->getPosition();
	Vec3 velocity = something->GetVelocity();

	BoundingSphere bound_sphere = something->getBound();
	BoundingSphere player_sphere = player_matrix->getBound();
	if(bound_sphere.intersects(player_sphere))
	{
		return true;
	}

	osgUtil::IntersectVisitor ivXY;
	osg::ref_ptr<osg::LineSegment> line[3];
	line[0] = new osg::LineSegment(now_position-Vec3(0, 0, 1), now_position+Vec3(0, 0, 1)); 
	line[1] = new osg::LineSegment(now_position-Vec3(0, 1, 0), now_position+Vec3(0, 1, 0));
	line[2] = new osg::LineSegment(now_position-Vec3(1, 0, 0), now_position+Vec3(1, 0, 0));
	
	for(int i=0; i<3; i++)
	{
		ivXY.addLineSegment(line[i]);
	}
	player_matrix->accept(ivXY) ;

	if(ivXY.hits())
	{
		return true;
	}
	return false;
}


