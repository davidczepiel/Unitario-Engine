#include "OverlayElement.h"
#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreMaterialManager.h>

OverlayElement::OverlayElement(std::string const& overlayName) : _overlay(nullptr)
{
	loadOverlay(overlayName);
}

OverlayElement::~OverlayElement()
{
	_overlay->clear();
}

void OverlayElement::loadOverlay(std::string const& overlayName)
{
	_overlay = Ogre::OverlayManager::getSingletonPtr()->getByName(overlayName);
	_overlay->show();
}

void OverlayElement::showOverlay()
{
	if (_overlay != nullptr)
		_overlay->show();
}

void OverlayElement::hideOverlay()
{
	if (_overlay != nullptr)
		_overlay->hide();
}

void OverlayElement::setMaterial(std::string const& containerName, std::string const& materialName)
{
	if(_overlay != nullptr)
		_overlay->getChild(containerName)->setMaterial(Ogre::MaterialManager::getSingletonPtr()->getByName(materialName));
}
