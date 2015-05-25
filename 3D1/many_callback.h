#ifndef _CALL_BACK_H_ 
#define _CALL_BACK_H_ 


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

#include "constant.h"


using namespace osg;
using namespace osgViewer;
using namespace std;

class z_camera_callback : public osg::NodeCallback
{
public:

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{ 
		
		//判断访问器类型
		if (nv->getVisitorType()==osg::NodeVisitor::EVENT_VISITOR)
		{	//创建一个事件访问器并初始化
			osgGA::EventVisitor* ev = dynamic_cast<osgGA::EventVisitor*>(nv);
			if (ev)
			{
				//得到执行动作
				osgGA::GUIActionAdapter* aa = ev->getActionAdapter();
				//得到事件队列
				osgGA::EventQueue::Events& events = ev->getEvents();

				for(osgGA::EventQueue::Events::iterator itr=events.begin();
					itr!=events.end(); ++itr)
				{
					//处理事件
					handle(*(*itr),*(aa));
				}
			}
		}
	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{ 
		//得到场景数据
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		//osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(viewer->getSceneData());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				//按下Key_Up时,向Z正方向平移一个单位
				if (ea.getKey()==osgGA::GUIEventAdapter::KEY_Up)
				{
					/*
					osg::Matrix mT,v;
					v.makeTranslate(0.0f,0.0f,1.0f);
					mT=mt->getMatrix();
					mT=mT*v;
					mt->setMatrix(mT);
					*/

					GAME.cow.state|=1;
				}

				//按下Key_Down时，向Z负方向平移一个单位
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Down)
				{
					GAME.cow.state|=2;
				}
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Left)
				{
					GAME.cow.state|=4;
				}
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Right)
				{
					GAME.cow.state|=8;
				}
				break;
			}
		case(osgGA::GUIEventAdapter::KEYUP):
			{
				
				if (ea.getKey()==osgGA::GUIEventAdapter::KEY_Down)
				{
					GAME.cow.state^=2;
				}

				//按下Key_Down时，向Z负方向平移一个单位
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Up)
				{
					GAME.cow.state^=1;
				}
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Left)
				{
					GAME.cow.state^=4;
				}
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Right)
				{
					GAME.cow.state^=8;
				}
				
				break;
				
			}
		default:

			break;
		}
		return false;
	}
};


class z_cow_callback :public osg::NodeCallback
{
public:
	z_cow_callback()
	{
		//
		angle=0.01;
	}

	virtual void operator()(osg::Node* node ,osg::NodeVisitor* nv)
	{
		

		//创建矩阵变换节点
		osg::MatrixTransform* mtCow = dynamic_cast<osg::MatrixTransform*>(node);
		//创建矩阵
		osg::Matrix mr,v;
		/*
		v.makeRotate(angle,osg::Vec3(0.0f,0.0f,1.0f));
		mr=mtCow->getMatrix();
		mr=mr*v;
		mtCow->setMatrix(mr);
		*/

		if(GAME.cow.inited==0)
		{
			    v.makeTranslate(0.0f,0.0f,100.0f);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);

				GAME.cow.inited=1;
		}



		if((GAME.cow.state&1)!=0)
		{
				v.makeTranslate(1.0f,0.0f,0.0f);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
		}
		
		if((GAME.cow.state&2)!=0)
		{
				v.makeTranslate(-1.0f,0.0f,0.0f);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
		}

		if((GAME.cow.state&4)!=0)
		{
				v.makeTranslate(0.0f,1.0f,0.0f);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
		}

		if((GAME.cow.state&8)!=0)
		{
				v.makeTranslate(0.0f,-1.0f,0.0f);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
		}
		//angle+= 0.01 ;

		//继续传递参数，执行其他设置回调的节点
		traverse( node, nv );
	}

public:

	//旋转角度
	double angle ;
};


#endif 