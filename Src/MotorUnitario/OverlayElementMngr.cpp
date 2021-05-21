#include "OverlayElementMngr.h"
#include "MotorGrafico/OverlayElementMngr.h"
#include "Exceptions.h"

OverlayElementMngr::OverlayElementMngr(std::string elementName)
{
	try {
		_overlayElement = new OgreOverlayElement(elementName);
	}
	catch(...){
		throw SourcePathException("The overlay element " + elementName + " doesn't exist");
	}
}

OverlayElementMngr::~OverlayElementMngr()
{
}

void OverlayElementMngr::setPosition(float left, float top)
{
	_overlayElement->setPosition(left, top);
}

void OverlayElementMngr::setEnabled(bool b)
{
	b ? _overlayElement->show() : _overlayElement->hide();
}

void OverlayElementMngr::setWidth(float w)
{
	_overlayElement->setWidth(w);
}

void OverlayElementMngr::setHeight(float h)
{
	_overlayElement->setHeight(h);
}

void OverlayElementMngr::setMaterial(std::string const& materialName){
	try {
		_overlayElement->setMaterial(materialName);
	}
	catch (...) {
		throw SourcePathException("The material " + materialName + " doesn't exist");
	}
}
