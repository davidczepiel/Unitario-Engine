#pragma once
#ifndef COMPONENTSFACTORY_H
#define COMPONENTSFACTORY_H
#include <string>
#include <map>
class ComponentFactory;
class Component;
static std::map<std::string, ComponentFactory*> _componentTranslator;

class ComponentsFactory
{
public:
	ComponentsFactory() {

	}
	~ComponentsFactory() {

	}
	/// <summary>
	/// adds a new component to the map
	/// </summary>
	/// <param name="name">The name component</param>
	/// <param name="factory">The equivalent factory</param>
	static void add(const std::string& name, ComponentFactory* factory);
	
	/// <summary>
	/// gets a component based in the name received
	/// </summary>
	/// <param name="name">The name of the desired component</param>
	/// <returns>The desired component</returns>
	static Component* getComponentByName(const std::string& name);

private:
	
};
#endif // !COMPONENTSFACTORY_H


