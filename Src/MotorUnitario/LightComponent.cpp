#include "LightComponent.h"
#include "Exceptions.h"

#include <string>

unsigned int LightComponent::_lightCount = 0;

LightComponent::LightComponent(const std::string& gameObjectName, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _id(_lightCount++), _lightComponent(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _lightComponent; _lightComponent = nullptr;
}