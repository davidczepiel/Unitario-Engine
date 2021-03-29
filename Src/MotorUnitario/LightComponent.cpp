#include "LightComponent.h"
#include "MotorGrafico/Light.h"

LightComponent::LightComponent(): Component(2, nullptr)
{
	_light->setDiffuse(5, 5, 5);
}
