#ifndef _SKYBOX_H_ 
#define _SKYBOX_H_ 

#include <osgViewer/Viewer>

#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Transform>
#include <osg/Material>
#include <osg/NodeCallback>
#include <osg/Depth>
#include <osg/CullFace>
#include <osg/TexMat>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/TextureCubeMap>

#include <osgDB/WriteFile>
#include <osgDB/ReadFile>

#include <osgUtil/Optimizer>

//��ȡ����ͼ
osg::TextureCubeMap* readCubeMap()
{
	osg::TextureCubeMap* cubemap = new osg::TextureCubeMap;

	osg::Image* imagePosX = osgDB::readImageFile("right.jpg");
	osg::Image* imageNegX = osgDB::readImageFile("left.jpg");
	osg::Image* imagePosY = osgDB::readImageFile("front.jpg");
	osg::Image* imageNegY = osgDB::readImageFile("back.jpg");
	osg::Image* imagePosZ = osgDB::readImageFile("up.jpg");
	osg::Image* imageNegZ = osgDB::readImageFile("down.jpg");

	if (imagePosX && imageNegX && imagePosY && imageNegY && imagePosZ && imageNegZ)
	{
		//��������ͼ�����������ͼ
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imagePosX);
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imageNegX);
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imagePosY);
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imageNegY);
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imagePosZ);
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imageNegZ);

		//����������ģʽ
		cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
		cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
		cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

		//�����˲������κ�mipmap
		cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
		cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	}

	return cubemap;
}
//����������ͼ����
struct TexMatCallback : public osg::NodeCallback
{
public:

	TexMatCallback(osg::TexMat& tm) :
	  _texMat(tm)
	  {
		  //
	  }

	  virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	  {
		  osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		  if (cv)
		  {
			  //�õ�ģ����ͼ����������ת�Ƕ�
			  const osg::Matrix& MV = *(cv->getModelViewMatrix());
			  const osg::Matrix R = osg::Matrix::rotate( osg::DegreesToRadians(112.0f), 0.0f,0.0f,1.0f)*
				  osg::Matrix::rotate( osg::DegreesToRadians(90.0f), 1.0f,0.0f,0.0f);

			  osg::Quat q = MV.getRotate();
			  const osg::Matrix C = osg::Matrix::rotate( q.inverse() );

			  //�����������
			  _texMat.setMatrix( C*R );
		  }

		  traverse(node,nv);
	  }

	  //�������
	  osg::TexMat& _texMat;
};


//һ���任�࣬ʹ��պ����ӵ���ת
class MoveEarthySkyWithEyePointTransform : public osg::Transform
{
public:
	//�ֲ����������������
	virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix,osg::NodeVisitor* nv) const 
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			osg::Vec3 eyePointLocal = cv->getEyeLocal();
			matrix.preMult(osg::Matrix::translate(eyePointLocal));
		}
		return true;
	}

	//����������Ϊ�ֲ�����
	virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix,osg::NodeVisitor* nv) const
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			osg::Vec3 eyePointLocal = cv->getEyeLocal();
			matrix.postMult(osg::Matrix::translate(-eyePointLocal));
		}
		return true;
	}
};


//������պ�
osg::Node* createSkyBox()
{
	osg::StateSet* stateset = new osg::StateSet();

	//��������ӳ�䷽ʽ��ָ��Ϊ�����ʽ���������е���ɫ����ԭ������ɫ
	osg::TexEnv* te = new osg::TexEnv;
	te->setMode(osg::TexEnv::REPLACE);
	stateset->setTextureAttributeAndModes(0, te, osg::StateAttribute::ON| osg::StateAttribute::OVERRIDE);

	//�Զ������������꣬���䷽ʽ(REFLECTION_MAP)
	/*
	NORMAL_MAP����׼ģʽ������ͼ����
	REFLECTION_MAP������ģʽ����������
	SPHERE_MAP������ģ�ͣ���������
	*/
	osg::TexGen *tg = new osg::TexGen;
	tg->setMode(osg::TexGen::NORMAL_MAP);
	stateset->setTextureAttributeAndModes(0, tg, osg::StateAttribute::ON| osg::StateAttribute::OVERRIDE);

	//�����������
	osg::TexMat *tm = new osg::TexMat;
	stateset->setTextureAttribute(0, tm);

	//��������ͼ����
	osg::TextureCubeMap* skymap = readCubeMap();
	stateset->setTextureAttributeAndModes(0, skymap, osg::StateAttribute::ON| osg::StateAttribute::OVERRIDE);

	stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	stateset->setMode( GL_CULL_FACE, osg::StateAttribute::OFF );

	//���������ΪԶƽ��
	osg::Depth* depth = new osg::Depth;
	depth->setFunction(osg::Depth::ALWAYS);
	depth->setRange(1.0,1.0);//Զƽ��   
	stateset->setAttributeAndModes(depth, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	//������Ⱦ˳��Ϊ-1������Ⱦ
	stateset->setRenderBinDetails(-1,"RenderBin");

	osg::Drawable* drawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),1));

	//��������뵽Ҷ�ڵ�
	osg::Geode* geode = new osg::Geode;
	geode->setCullingActive(false);
	geode->setStateSet( stateset );
	geode->addDrawable(drawable);

	//���ñ任
	osg::Transform* transform = new MoveEarthySkyWithEyePointTransform();
	transform->setCullingActive(false);
	transform->addChild(geode);

	osg::ClearNode* clearNode = new osg::ClearNode;
	clearNode->setCullCallback(new TexMatCallback(*tm));
	clearNode->addChild(transform);

	return clearNode;
}


#endif 