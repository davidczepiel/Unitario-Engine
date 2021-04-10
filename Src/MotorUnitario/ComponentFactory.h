#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"
#include "ImageRenderComponent.h"
#include "LightComponent.h"
#define FACTORY(name) virtual name* create(){return new name();}


class ComponentFactory
{
public:
	virtual Component* create() = 0;

protected:
	ComponentFactory() {

	}
	virtual ~ComponentFactory() {}
};
#endif // !COMPONENTFACTORY_H

#ifndef IMAGERENDERFACTORY_H
#define IMAGERENDERFACTORY_H_H

class ImageRenderFactory : public ComponentFactory
{
public:
	ImageRenderFactory():ComponentFactory() {}
	
	virtual ~ImageRenderFactory() {}

	FACTORY(ImageRenderComponent)

};
#endif // !IMAGERENDERFACTORY_H

#ifndef IMAGERENDERFACTORY_H
#define IMAGERENDERFACTORY_H

class LightComponentFactory : public ComponentFactory
{
public:
	LightComponentFactory() :ComponentFactory() {}

	virtual ~LightComponentFactory() {}

	FACTORY(LightComponent)

};
#endif // !IMAGERENDERFACTORY_H