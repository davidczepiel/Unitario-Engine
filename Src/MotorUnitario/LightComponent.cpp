#include "LightComponent.h"
#include "ComponentIDs.h"
#include "GameObject.h"

LightComponent::LightComponent() :Component(ComponentId::LightComponent)
{
}

LightComponent::LightComponent(GameObject* gameObject): Component(ComponentId::LightComponent, gameObject), _light(nullptr)
{
	_light = new Light(gameObject->getName());
}

LightComponent::~LightComponent()
{
	delete _light; _light = nullptr;
}
