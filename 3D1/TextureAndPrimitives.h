#pragma once

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Image>
#include <osg/TexGen>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <osg/StateSet>
#include <osg/Geometry>
#include <osg/Billboard>

//创建一个四边形节点
osg::Node* createBillBoard(osg::Image* );


//创建二维纹理状态对象
osg::StateSet* createTexture2DState(osg::Image* image);