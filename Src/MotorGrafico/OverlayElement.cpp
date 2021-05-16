#include "OverlayElement.h"
#include "GraphicsEngine.h"
#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <SDL_video.h>

OverlayElement::OverlayElement() : _overlay(nullptr)
{
}

OverlayElement::~OverlayElement()
{
	_overlay->clear();
	//delete _overlay;
}

void OverlayElement::loadOverlay(std::string const& overlayName)
{
	_overlay = Ogre::OverlayManager::getSingletonPtr()->getByName(overlayName);
	_overlay->show();
}

void OverlayElement::showOverlay(std::string const& containerName)
{
	if (_overlay != nullptr) {
		if (containerName == " ")
			_overlay->show();
		else
			_overlay->getChild(containerName)->show();
	}
}

void OverlayElement::hideOverlay(std::string const& containerName)
{
	if (_overlay != nullptr) {
		if (containerName == " ")
			_overlay->show();
		else
			_overlay->getChild(containerName)->hide();
	}
}

void OverlayElement::setMaterial(std::string const& containerName, std::string const& materialName)
{
	if(_overlay != nullptr)
		_overlay->getChild(containerName)->setMaterial(Ogre::MaterialManager::getSingletonPtr()->getByName(materialName));
}

std::pair<int, int> OverlayElement::getPosition(std::string const& containerName)
{
	double x = static_cast<double>(_overlay->getChild(containerName)->getLeft());
	double y = static_cast<double>(_overlay->getChild(containerName)->getTop());

	std::pair<int, int> windowSize = GraphicsEngine::getInstance()->getWindowSize();
	return std::pair<int, int>((int)(x * windowSize.first), (int)(y * windowSize.second));
}


std::pair<int, int> OverlayElement::getSize(std::string const& containerName)
{
	double x = static_cast<double>(_overlay->getChild(containerName)->getWidth());
	double y = static_cast<double>(_overlay->getChild(containerName)->getHeight());

	std::pair<int, int> windowSize = GraphicsEngine::getInstance()->getWindowSize();

	return std::pair<int, int>((int)(x * windowSize.first), (int)(y * windowSize.second));
}



