#include "ImageRender.h"
#include <OgreSceneNode.h>
#include <OgreBillboardSet.h>

ImageRender::ImageRender():_billboardSet(nullptr),_billboardSetNode(nullptr)
{
	//Here we should create the billboard,but we need a SceneManager ???

	/*_billboardSet = mSM->createBillboardSet("BBSet", 1);
	_billboardSet->createBillboard(mNode->getPosition());

	_billboardSetNode = mNode->createChildSceneNode("NodeName");
	_billboardSetNode->attachObject(_billboardSet);*/
}

ImageRender::~ImageRender()
{
}

void ImageRender::setDefaultDimensions(float width, float height)
{
	_billboardSet->setDefaultDimensions(width, height); 
}

void ImageRender::setMaterialName(const std::string& name)
{
	_billboardSet->setMaterialName(name);
}

void ImageRender::setVisible(bool visible)
{
	_billboardSetNode->setVisible(visible);
}

void ImageRender::setBillboardOrigin(BillboardOrigin type)
{
	_billboardSet->setBillboardOrigin((Ogre::BillboardOrigin)type);
}

void ImageRender::setBillboardType(BillboardType type)
{
	_billboardSet->setBillboardType((Ogre::BillboardType)type);
}
