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

//����һ���ı��νڵ�
osg::Node* createBillBoard(osg::Image* );


//������ά����״̬����
osg::StateSet* createTexture2DState(osg::Image* image);