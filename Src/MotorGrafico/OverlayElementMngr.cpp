#include "OverlayElementMngr.h"
#include <OgreOverlayManager.h>
#include <OgreOverlayElement.h>
#include <OgreMaterialManager.h>

OgreOverlayElement::OgreOverlayElement(std::string elementName)
{
	_overlayElement = static_cast<Ogre::OverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->getOverlayElement(elementName));
}

OgreOverlayElement::~OgreOverlayElement()
{
}

void OgreOverlayElement::setPosition(float left, float top)
{
	_overlayElement->setPosition(left, top);
}

void OgreOverlayElement::setMaterial(std::string materialName)
{
	_overlayElement->setMaterial(Ogre::MaterialManager::getSingletonPtr()->getByName(materialName));
}

void OgreOverlayElement::setWidth(float w)
{
	_overlayElement->setWidth(w);
}

void OgreOverlayElement::setHeight(float h)
{
	_overlayElement->setHeight(h);
}

void OgreOverlayElement::setEnabled(bool b)
{
	_overlayElement->setEnabled(b);
}

void OgreOverlayElement::show()
{
	_overlayElement->show();
}

void OgreOverlayElement::hide()
{
	_overlayElement->hide();
}
