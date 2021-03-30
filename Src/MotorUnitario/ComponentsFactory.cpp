#include "ComponentsFactory.h"
#include "ComponentFactory.h"
#include "Exceptions.h"

void ComponentsFactory::add(const std::string& name, ComponentFactory* factory)
{
	_componentTranslator.insert(std::make_pair(name, factory));
}

ComponentFactory* ComponentsFactory::getComponentByName(const std::string& name)
{
	auto it = _componentTranslator.find(name);
	if (it == _componentTranslator.end())
		throw ComponentException("This component doesn't exist");
	return (*it).second->create();
}
