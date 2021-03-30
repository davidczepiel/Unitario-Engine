#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#define FACTORY(name) virtual name* create(){return new name();}
class ComponentFactory
{
public:
	virtual ComponentFactory* create() = 0;

private:
	ComponentFactory() {

	}
	virtual ~ComponentFactory() {}
};
#endif // !COMPONENTFACTORY_H
