#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "ComponentsFactory.h"

class ComponentFactory
{
public:
	virtual Component* create() const = 0;
};

class FactoryAdder {
public: 
	FactoryAdder(ComponentFactory* factory, const char* name) {
		ComponentsFactory::getInstance()->add(name, factory);
	}
};

/// <summary>
/// This is a macro that defines a factoryComponent class
/// </summary>
/// <param name="cmp">The component that returns the class</param>
#define CMP_FACTORY(cmp)										\
class cmp##Factory : public ComponentFactory					\
{																\
public:															\
    virtual Component* create() const { return new cmp(); };	\
};																\


#endif