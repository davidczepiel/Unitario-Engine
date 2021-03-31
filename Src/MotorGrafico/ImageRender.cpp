#include "ImageRender.h"

ImageRender::ImageRender():_billboardSet(nullptr),_billboardSetNode(nullptr)
{
	//Here we should create the billboard,but we need a SceneManager

	/*_billboardSet = mSM->createBillboardSet("BBSet", 1);
	_billboardSet->createBillboard(mNode->getPosition());

	_billboardSetNode = mNode->createChildSceneNode("NodeName");
	_billboardSetNode->attachObject(_billboardSet);*/
}

ImageRender::~ImageRender()
{
}
