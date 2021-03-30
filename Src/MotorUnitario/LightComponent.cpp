#include "LightComponent.h"
#include "ComponentIDs.h"

LightComponent::LightComponent(GameObject* gameObject): Component(ComponentId::LightComponent, gameObject), _light(nullptr)
{
	//TODO: initialize Light's using sceneNode from transform or whatever, i dunno
}

LightComponent::~LightComponent()
{
}
