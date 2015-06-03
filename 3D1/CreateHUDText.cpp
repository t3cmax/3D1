#include "CreateHUDText.h"

osg::Camera* createHUDText(osgText::Text* text)
{
	osg::Camera* camera = new osg::Camera() ;

	//设置投影矩阵
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0,1280,0,800));

	//设置视图矩阵，同时确保不被场景其他图形位置变换影响，使用绝对帧引用
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewMatrix(osg::Matrix::identity());

	//清除深度缓存
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);

	//设置渲染顺序为POST
	camera->setRenderOrder(osg::Camera::POST_RENDER);

	//设置为不接收事件，始终不得到焦点
	camera->setAllowEventFocus(false);

	osg::Geode* geode = new osg::Geode() ;
	geode->setDataVariance(osg::Geometry::DYNAMIC);

	osg::StateSet* stateset = geode->getOrCreateStateSet() ;
	//关闭光照
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	//关闭深度测试
	stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);

	geode->addDrawable(text);

	camera->addChild(geode);

	return camera ;
}