#ifndef _CALL_BACK_H_ 
#define _CALL_BACK_H_ 

#include<iostream>
#include "osgheaders.h"

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
					GAME.cow.state|=16;
				}
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Right)
				{
					GAME.cow.state|=32;
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
					GAME.cow.state^=16;
				}
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Right)
				{
					GAME.cow.state^=32;
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
	int cnt;


	z_cow_callback()
	{
		//
		angle=0.01;
		cnt=0;

	}

	virtual void operator()(osg::Node* node ,osg::NodeVisitor* nv)
	{

		//��������任�ڵ�
		osg::MatrixTransform* mtCow = dynamic_cast<osg::MatrixTransform*>(node);
		//��������
		osg::Matrix mr,v,ori;
		osg::Vec3 mov3;
		osg::Vec3 pos1,pos2;
		/*
		v.makeRotate(angle,osg::Vec3(0.0f,0.0f,1.0f));
		mr=mtCow->getMatrix();
		mr=mr*v;
		mtCow->setMatrix(mr);
		*/
		
		/*cnt++;
		if(cnt>=100)
		{
			mtCow->getOrCreateStateSet()->setAttributeAndModes(program_red, osg::StateAttribute::Values::ON);
		}
		if(cnt>=1000)
		{
			mtCow->getOrCreateStateSet()->setAttributeAndModes(program_normal, osg::StateAttribute::Values::ON);
		}*/

		if(GAME.cow.inited==0)
		{
			    
				mr=mtCow->getMatrix();
				v.makeRotate(osg::PI,osg::Vec3(0.0f,0.0f,1.0f));

				mr=mr*v;

				v.makeTranslate(-22.0f, -224.0f, 99.0f);
				mr=mr*v;

				mtCow->setMatrix(mr);

				GAME.cow.inited=1;
				GAME.cow.dir=osg::PI_2;
		}



		if((GAME.cow.state&1)!=0)
		{
				mov3=osg::Vec3(1.0f,0.0f,0.0f);
				v.makeRotate(GAME.cow.dir,osg::Vec3(0.0f,0.0f,1.0f));
				mov3=mov3*v;

			    v.makeTranslate(mov3);
				ori=mr=mtCow->getMatrix();
				pos1=osg::Vec3(0.0f,0.0f,0.0f)*mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
				pos2=osg::Vec3(0.0f,0.0f,0.0f)*mtCow->getMatrix();

				//cout<<pos1._v[0]<<' '<<pos1._v[1]<<' '<<pos1._v[2]<<"      "<<pos2._v[0]<<' '<<pos2._v[1]<<' '<<pos2._v[2]<<endl;
				//while(1);

				if(check_into_ground(node,pos1,pos2)==false)
				{
					mtCow->setMatrix(ori);
				}
				else
				{
				////////////////////////
				    GAME.main_camera->ChangePosition(osg::Vec3 (0, GAME.main_camera->m_fMoveSpeed * sinf(osg::PI_2+GAME.main_camera->m_vRotation._v[2]), 0)) ; 
                    GAME.main_camera->ChangePosition(osg::Vec3 (GAME.main_camera->m_fMoveSpeed * cosf(osg::PI_2+GAME.main_camera->m_vRotation._v[2]), 0, 0)) ;
				}
		}
		
		if((GAME.cow.state&2)!=0)
		{
				mov3=osg::Vec3(-1.0f,0.0f,0.0f);
				v.makeRotate(GAME.cow.dir,osg::Vec3(0.0f,0.0f,1.0f));
				mov3=mov3*v;

			    v.makeTranslate(mov3);
				ori=mr=mtCow->getMatrix();
				pos1=osg::Vec3(0.0f,0.0f,0.0f)*mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
				pos2=osg::Vec3(0.0f,0.0f,0.0f)*mtCow->getMatrix();
				////////////////////////

				if(check_into_ground(node,pos1,pos2)==false)
				{
					mtCow->setMatrix(ori);
				}
				else
				{
				    GAME.main_camera->ChangePosition(osg::Vec3 (0, -GAME.main_camera->m_fMoveSpeed * sinf(osg::PI_2+GAME.main_camera->m_vRotation._v[2]), 0)) ; 
		            GAME.main_camera->ChangePosition(osg::Vec3(-GAME.main_camera->m_fMoveSpeed * cosf(osg::PI_2+GAME.main_camera->m_vRotation._v[2]), 0, 0)) ;
				}
		}

		if((GAME.cow.state&4)!=0)
		{
				mov3=osg::Vec3(0.0f,1.0f,0.0f);
				v.makeRotate(GAME.cow.dir,osg::Vec3(0.0f,0.0f,1.0f));
				mov3=mov3*v;
			    v.makeTranslate(mov3);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
		}

		if((GAME.cow.state&8)!=0)
		{
				mov3=osg::Vec3(0.0f,-1.0f,0.0f);
				v.makeRotate(GAME.cow.dir,osg::Vec3(0.0f,0.0f,1.0f));
				mov3=mov3*v;

			    v.makeTranslate(mov3);
				mr=mtCow->getMatrix();
				mr=mr*v;
				mtCow->setMatrix(mr);
		}

		if((GAME.cow.state&16)!=0)
		{
			
			mr=mtCow->getMatrix();
			v.makeRotate(osg::DegreesToRadians(GAME.main_camera->m_fAngle),osg::Vec3(0.0f,0.0f,1.0f));
			mr=v*mr;
			mtCow->setMatrix(mr);
			
			/////////////////////////
			//v.makeTranslate(GAME.main_camera->m_vPosition);
			
			/*
			mov3=GAME.main_camera->m_vPosition;
			mr=mtCow->getMatrix();
			mov3=mov3*mr.inverse(mr);
			v.makeRotate(osg::DegreesToRadians(GAME.main_camera->m_fAngle),osg::Vec3(0.0f,0.0f,1.0f));
			mov3=mov3*v;
			mov3=mov3*mr;
			GAME.main_camera->m_vPosition=mov3;
			*/

			GAME.main_camera->m_vRotation._v[2] += osg::DegreesToRadians(GAME.main_camera->m_fAngle);
			
			GAME.cow.dir+=osg::DegreesToRadians(GAME.main_camera->m_fAngle);
			//////////////////////////////////////////////////////////////////
			mr=mtCow->getMatrix();
			mov3=osg::Vec3(0.0f,0.9f,0.8f);
			mov3=mov3*mr;
			GAME.main_camera->m_vPosition=mov3;
			//m_vPosition = osg::Vec3(-22.0f, -224.9f, 99.8f);
            //m_vRotation = osg::Vec3((osg::PI_4)+0.6f, 0.0f, 0.0f);	

		}
		if((GAME.cow.state&32)!=0)
		{
			
			mr=mtCow->getMatrix();
			v.makeRotate(-osg::DegreesToRadians(GAME.main_camera->m_fAngle),osg::Vec3(0.0f,0.0f,1.0f));
			mr=v*mr;
			mtCow->setMatrix(mr);
			
			/////////////////////////////
			/*
			mov3=GAME.main_camera->m_vPosition;
			mr=mtCow->getMatrix();
			mov3=mov3*mr.inverse(mr);
			v.makeRotate(osg::DegreesToRadians(-GAME.main_camera->m_fAngle),osg::Vec3(0.0f,0.0f,1.0f));
			mov3=mov3*v;
			mov3=mov3*mr;
			GAME.main_camera->m_vPosition=mov3;
			*/

			GAME.main_camera->m_vRotation._v[2] -= osg::DegreesToRadians(GAME.main_camera->m_fAngle);
			
			GAME.cow.dir-=osg::DegreesToRadians(GAME.main_camera->m_fAngle);
			////////////////////////////////////////////////////////////
			mr=mtCow->getMatrix();
			mov3=osg::Vec3(0.0f,0.9f,0.8f);
			mov3=mov3*mr;
			GAME.main_camera->m_vPosition=mov3;
		}
		//angle+= 0.01 ;

		//�������ݲ�����ִ���������ûص��Ľڵ�
		traverse( node, nv );
	}
	
	bool check_into_ground(osg::Node* node,osg::Vec3 pos1,osg::Vec3 pos2)
	{
		bool first=0;
		bool flag;
		int times=0;
		while(1)
		{
		
			osgUtil::IntersectVisitor ivXY; 
			//�����µ�λ�õõ������߶μ��
			osg::ref_ptr<osg::LineSegment> lineXY = new osg::LineSegment(pos2+(pos2-pos1)*1.0,pos2+(pos2-pos1)*4.0); 

			osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(pos2+(pos2-pos1)*1.0+osg::Vec3(0.0f,0.0f,1.0f),pos2+(pos2-pos1)*1.0-osg::Vec3(0.0f,0.0f,1.0f)) ;

			ivXY.addLineSegment(lineZ.get()) ;

			ivXY.addLineSegment(lineXY.get()) ;
			//�ṹ�������
			GAME.main_camera->m_pHostViewer->getSceneData()->accept(ivXY) ;
			//->accept(ivXY) ;
			//���û����ײ���
			if(!ivXY.hits())
			{
				//cout<<"YYYYYYYYYYYYYY"<<endl;
			
				if(first==0)
				{
					first=1;
					flag=0;
				}
				else
				{
					if(flag==1)
					{
						break;
					}
					else
					{
						move_a_bit(node,osg::Vec3(0.0f,0.0f,-0.1f));
						pos2=pos2+osg::Vec3(0.0f,0.0f,-0.1f);
						pos1=pos1+osg::Vec3(0.0f,0.0f,-0.1f);
						//cout<<"!!!!!!!!!!!!!!"<<endl;
						times++;
					}
				}
			
			}
			else
			{
				//cout<<"HHHHHHHHHHHHHHHH"<<endl;
				//osgUtil::LineSegmentIntersector::Intersections::iterator hitr = ivXY.();  
				//osg::Vec3 vec3_p1 =hitr->getWorldIntersectPoint(); //�����õ��Ľ�����Ǿ��Ե����������ˡ�
			
				if(first==0)
				{
					first=1;
					flag=1;
				}
				else
				{
					if(flag==0)
					{
						break;
					}
					else
					{
						if(times<=10)
						{
							move_a_bit(node,osg::Vec3(0.0f,0.0f,0.1f));
							pos2=pos2+osg::Vec3(0.0f,0.0f,0.1f);
							pos1=pos1+osg::Vec3(0.0f,0.0f,0.1f);
							//cout<<pos1._v[2]<<' '<<pos2._v[2]<<"((((((((((("<<endl;
							times++;
						}
						else
						{
							GAME.main_camera->m_vPosition -= osg::Vec3(0.0f,0.0f,0.1f)*times;
							return false;
						}
					}
				}
			
			}

		}
		return true;
	}
	
	void move_a_bit(osg::Node* node,osg::Vec3 dat)
	{
		//cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		//��������任�ڵ�
		osg::MatrixTransform* mtCow = dynamic_cast<osg::MatrixTransform*>(node);
		//��������
		osg::Matrix mr,v;
		osg::Vec3 mov3;
		
		GAME.main_camera->m_vPosition += dat;
		mov3=dat;
		v.makeRotate(GAME.cow.dir,osg::Vec3(0.0f,0.0f,1.0f));
		mov3=mov3*v;

	    v.makeTranslate(mov3);
		mr=mtCow->getMatrix();
		mr=mr*v;
		mtCow->setMatrix(mr);
		return ;
	}

public:

	//��ת�Ƕ�
	double angle ;
};

/*class BombCallback : public osg::NodeCallback
{
public:
	Vec3 start_position;
	Vec3 velocity;
	Node* ground;
	Geometry *geometry;

public:
	BombCallback(Vec3 start_pos)
	{
		start_position = start_pos;
		velocity.set(Vec3(0.1,0,0));
	}

	virtual void operator()(osg::Node* node ,osg::NodeVisitor* nv)
	{
		using namespace osg;
		MatrixTransform* matrix_node = dynamic_cast<MatrixTransform*>(node);
		Matrix matrix = matrix_node->getMatrix();

		velocity += Vec3(0, 0, -0.002);

		matrix.postMultTranslate(velocity);

		matrix_node->setMatrix(matrix);

		Vec3 now_position = start_position * matrix;

		osgUtil::IntersectVisitor ivXY; 
		//�����µ�λ�õõ������߶μ��
		osg::ref_ptr<osg::LineSegment> lineXY = new osg::LineSegment(now_position, now_position+velocity); 

		ivXY.addLineSegment(lineXY);
		//�ṹ�������
		GAME.main_camera->m_pHostViewer->getSceneData()->accept(ivXY) ;
		if(ivXY.hits())
		{
			;
		}
		return;
	}
};*/

#endif 