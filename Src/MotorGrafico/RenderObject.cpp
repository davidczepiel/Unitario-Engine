#include "RenderObject.h"
#include "GraphicsEngine.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreQuaternion.h>
#include <OgreSceneManager.h>
#include <OgreMesh.h>

RenderObject::RenderObject(std::string const& meshName, std::string const& objectName) :
	_objectNode(nullptr), _objectEntity(nullptr), _objectName(objectName), _meshName(meshName), _meshSize()
{
}

RenderObject::~RenderObject()
{
	if (_objectEntity != nullptr) GraphicsEngine::getInstance()->getSceneManager()->destroyEntity(_objectEntity);
}

void RenderObject::init()
{
	Ogre::SceneManager* sM = GraphicsEngine::getInstance()->getSceneManager();
	_objectNode = sM->getSceneNode(_objectName);
	_objectEntity = sM->createEntity(_meshName);
	_objectNode->attachObject(_objectEntity);

	Ogre::Vector3 s = _objectEntity->getMesh()->getBounds().getSize();
	_meshSize = { s.x, s.y, s.z };
}

void RenderObject::setMaterial(std::string const& materialName)
{
	_objectEntity->setMaterialName(materialName);
}

void RenderObject::setPosition(float x, float y, float z)
{
	_objectNode->setPosition(Ogre::Vector3(x, y, z));
}

void RenderObject::setRotation(float x, float y, float z, float w)
{
	_objectNode->setOrientation(w, x, y, z);
}

const std::tuple<float, float, float>& RenderObject::getMeshSize()
{
	return _meshSize;
}

void RenderObject::rotate(float angle, float x, float y, float z)
{
	_objectNode->rotate(Ogre::Vector3(x, y, z), (Ogre::Radian)angle);
}

void RenderObject::setScale(float x, float y, float z)
{
	_objectNode->setScale(Ogre::Vector3(x / std::get<0>(_meshSize), y / std::get<1>(_meshSize), z / std::get<2>(_meshSize)));
}

void RenderObject::scale(float x, float y, float z)
{
	_objectNode->scale(Ogre::Vector3(x, y, z));
}

void RenderObject::lookAt(float x, float y, float z)
{
	_objectNode->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TransformSpace::TS_WORLD, Ogre::Vector3::UNIT_Z);
}

void RenderObject::setVisible(bool visible)
{
	_objectEntity->setVisible(visible);
}

void RenderObject::setCastShadows(bool castShadows)
{
	_objectEntity->setCastShadows(castShadows);
}

void RenderObject::setRenderingDistance(float distance)
{
	_objectEntity->setRenderingDistance(distance);
}