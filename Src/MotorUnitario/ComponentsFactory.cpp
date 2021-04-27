#include "ComponentsFactory.h"
#include "ComponentFactory.h"
#include "Exceptions.h"
#include "Component.h"
#include "Logger.h"

std::unique_ptr<ComponentsFactory> ComponentsFactory::instance = nullptr;

ComponentsFactory* ComponentsFactory::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new ComponentsFactory());
	}
	return instance.get();
}

ComponentsFactory::~ComponentsFactory()
{
	for (auto it : _componentTranslator) {
		delete it.second; 
	}
	_componentTranslator.clear();
}

void ComponentsFactory::add(const std::string& name, ComponentFactory* factory)
{
	_componentTranslator.insert(std::make_pair(name, factory));
	Logger::getInstance()->log(name + " inserted");
}

Component* ComponentsFactory::getComponentByName(const std::string& name)
{
	auto it = _componentTranslator.find(name);
	if (it == _componentTranslator.end())
		throw ComponentException("The component " + name + " doesn't exist");
	return (*it).second->create();
}
