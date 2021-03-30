#pragma once
#include <iostream>
#define FACTORY(name) virtual name* create(){return new name();}
class ComponentFactory
{
public:
	ComponentFactory() {

	}
	virtual ~ComponentFactory() {}
	virtual ComponentFactory* create() {}

};
