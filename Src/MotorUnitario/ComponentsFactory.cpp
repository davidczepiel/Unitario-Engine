#include "ComponentsFactory.h"
#include "ComponentFactory.h"
#include "Exceptions.h"
#include "Component.h"

ComponentsFactory* ComponentsFactory::instance = nullptr;

ComponentsFactory* ComponentsFactory::getInstance()
{
	if (instance == nullptr) {
		instance = new ComponentsFactory();
	}
	return instance;
}

ComponentsFactory::~ComponentsFactory()
{
	for (auto it : _componentTranslator) {
		delete it.second; 
	}
	_componentTranslator.clear();
	Logger::getInstance()->log("Destrucción");
}

void ComponentsFactory::add(const std::string& name, ComponentFactory* factory)
{
	if (!_componentTranslator.insert(std::make_pair(name, factory)).second)
		delete factory;
}

Component* ComponentsFactory::getComponentByName(const std::string& name)
{
	auto it = _componentTranslator.find(name);
	if (it == _componentTranslator.end())
		throw ComponentException("The component " + name + " doesn't exist");
	return (*it).second->create();
}
