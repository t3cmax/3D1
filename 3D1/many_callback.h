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
		
		//�жϷ���������
		if (nv->getVisitorType()==osg::NodeVisitor::EVENT_VISITOR)
		{	//����һ���¼�����������ʼ��
			osgGA::EventVisitor* ev = dynamic_cast<osgGA::EventVisitor*>(nv);
			if (ev)
			{
				//�õ�ִ�ж���
				osgGA::GUIActionAdapter* aa = ev->getActionAdapter();
				//�õ��¼�����
				osgGA::EventQueue::Events& events = ev->getEvents();

				for(osgGA::EventQueue::Events::iterator itr=events.begin();
					itr!=events.end(); ++itr)
				{
					//�����¼�
					handle(*(*itr),*(aa));
				}
			}
		}
	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{ 
		//�õ���������
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		//osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(viewer->getSceneData());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				//����Key_Upʱ,��Z������ƽ��һ����λ
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

				//����Key_Downʱ����Z������ƽ��һ����λ
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

				//����Key_Downʱ����Z������ƽ��һ����λ
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
		

		//��������任�ڵ�
		osg::MatrixTransform* mtCow = dynamic_cast<osg::MatrixTransform*>(node);
		//��������
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

		//�������ݲ�����ִ���������ûص��Ľڵ�
		traverse( node, nv );
	}

public:

	//��ת�Ƕ�
	double angle ;
};


#endif 