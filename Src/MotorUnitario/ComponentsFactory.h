#pragma once
#include <string>
#include <map>
class ComponentFactory;
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
	static void add(std::string name, ComponentFactory* factory);
	
	/// <summary>
	/// gets a component based in the name received
	/// </summary>
	/// <param name="name">The name of the desired component</param>
	/// <returns>The desired component</returns>
	static ComponentFactory* getComponentByName(std::string name);
private:
	static std::map<std::string, ComponentFactory*> _componentTranslator;
};

