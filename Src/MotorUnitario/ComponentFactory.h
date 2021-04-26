#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

class Component;

/// <summary>
/// This is a macro that defines a factoryComponent class
/// </summary>
/// <param name="factoryName">Class of the factory we want to create</param>
/// <param name="cmp">The component that returns the class</param>
#define CMP_FACTORY(factoryName,cmp)						\
class factoryName : public ComponentFactory					\
{                                                           \
public:                                                     \
    virtual cmp* create() const { return new cmp(); };		\
};															\

class ComponentFactory
{
public:
	virtual Component* create() const = 0;
};

#endif