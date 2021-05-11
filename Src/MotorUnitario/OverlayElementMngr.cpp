#include "OverlayElementMngr.h"
#include "MotorGrafico/OverlayElementMngr.h"

OverlayElementMngr::OverlayElementMngr(std::string elementName)
{
	_overlayElement = new OgreOverlayElement(elementName);
}

OverlayElementMngr::~OverlayElementMngr()
{
}

void OverlayElementMngr::setPosition(float left, float top)
{
	_overlayElement->setPosition(left, top);
}

void OverlayElementMngr::setEnabled(bool hide)
{
	_overlayElement->setEnabled(hide);
}

void OverlayElementMngr::setWidth(float w)
{
	_overlayElement->setWidth(w);
}

void OverlayElementMngr::setHeight(float h)
{
	_overlayElement->setHeight(h);
}

void OverlayElementMngr::setMaterial(std::string const& materialName)
{
	_overlayElement->setMaterial(materialName);
}
