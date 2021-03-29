#pragma once
#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "Component.h"

class Light;

class LightComponent: Component
{
public:

	LightComponent();

private:
	Light* _light;

};

#endif LIGHT_COMPONENT_H