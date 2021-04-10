#include "LightComponent.h"
#include "Exceptions.h"

#include <string>

#include <iostream>

unsigned int LightComponent::_lightCount = 0;

LightComponent::LightComponent():Component(1),_id(0)
{
	std::cout << "LIGHT CREADO";
}

LightComponent::LightComponent(const std::string& gameObjectName, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _id(_lightCount++), _lightComponent(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _lightComponent; _lightComponent = nullptr;
}