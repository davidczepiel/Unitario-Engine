#include "RenderObject.h"
#include "GraphicsEngine.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreQuaternion.h>
#include <OgreSceneManager.h>

RenderObject::RenderObject(std::string const& meshName, std::string const& objectName) : _objectNode(nullptr), _objectEntity(nullptr), _objectName(objectName), _meshName(meshName)
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::init()
{
	Ogre::SceneManager* sM = GraphicsEngine::getInstance()->getSceneManager();
	_objectNode = sM->getSceneNode(_objectName);
	_objectEntity = sM->createEntity(_meshName);
	_objectNode->attachObject(_objectEntity);
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

void RenderObject::setAlpha(float alpha)
{
	for (Ogre::SubEntity* i : _objectEntity->getSubEntities())
	{
		for (Ogre::Technique* tech : i->getMaterial()->getTechniques())
		{
			for (Ogre::Pass* pass : tech->getPasses())
			{
				pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
				pass->setCullingMode(Ogre::CullingMode::CULL_NONE);
				pass->setManualCullingMode(Ogre::ManualCullingMode::MANUAL_CULL_FRONT);
				Ogre::ColourValue col = pass->getDiffuse();
				pass->setDiffuse(col.r, col.g, col.b, alpha);
			}
		}
	}
}
void RenderObject::rotate(float angle, float x, float y, float z)
{
	_objectNode->rotate(Ogre::Vector3(x, y, z), (Ogre::Radian)angle);
}

void RenderObject::setScale(float x, float y, float z)
{
	_objectNode->setScale(Ogre::Vector3(x, y, z));
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