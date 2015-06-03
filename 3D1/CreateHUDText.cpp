#include "CreateHUDText.h"

osg::Camera* createHUDText(osgText::Text* text)
{
	osg::Camera* camera = new osg::Camera() ;

	//����ͶӰ����
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0,1280,0,800));

	//������ͼ����ͬʱȷ��������������ͼ��λ�ñ任Ӱ�죬ʹ�þ���֡����
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewMatrix(osg::Matrix::identity());

	//�����Ȼ���
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);

	//������Ⱦ˳��ΪPOST
	camera->setRenderOrder(osg::Camera::POST_RENDER);

	//����Ϊ�������¼���ʼ�ղ��õ�����
	camera->setAllowEventFocus(false);

	osg::Geode* geode = new osg::Geode() ;
	geode->setDataVariance(osg::Geometry::DYNAMIC);

	osg::StateSet* stateset = geode->getOrCreateStateSet() ;
	//�رչ���
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	//�ر���Ȳ���
	stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);

	geode->addDrawable(text);

	camera->addChild(geode);

	return camera ;
}