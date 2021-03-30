#include "RenderObject.h"
#include <OgreQuaternion.h>

RenderObject::RenderObject(std::string meshName)
{
	//SceneManager instance will create a scene node for this object here

	//Need the sceneManager to create a new entity with mesh
	//objectEntity = sceneManager->createEntity(meshName);
	objectNode->attachObject(objectEntity);
}

RenderObject::~RenderObject()
{
}

void RenderObject::setMaterial(std::string materialName)
{
	objectEntity->setMaterialName(materialName);
}

void RenderObject::setPosition(float x, float y, float z)
{
	objectNode->setPosition(Ogre::Vector3(x, y, z));
}

void RenderObject::setOrientation(float angle, float x, float y, float z)
{
	objectNode->setOrientation(Ogre::Quaternion((Ogre::Radian)angle, Ogre::Vector3(x, y, z)));
}

void RenderObject::rotate(float angle, float x, float y, float z)
{
	objectNode->rotate(Ogre::Vector3(x, y, z), (Ogre::Radian)angle);
}

void RenderObject::setScale(float x, float y, float z)
{
	objectNode->setScale(Ogre::Vector3(x, y, z));
}

void RenderObject::scale(float x, float y, float z)
{
	objectNode->scale(Ogre::Vector3(x, y, z));
}

void RenderObject::setVisible(bool visible)
{
	objectNode->setVisible(visible);
}

void RenderObject::setCastShadows(bool castShadows)
{
	objectEntity->setCastShadows(castShadows);
}

void RenderObject::setRenderingDistance(float distance)
{
	objectEntity->setRenderingDistance(distance);
}
