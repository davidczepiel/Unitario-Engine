#pragma once
#ifndef OVERLAYCOMPONENT_H
#define OVERLAYCOMPONENT_H

#include "Component.h"
#include <string>

class GameObject;
class OverlayElement;

class OverlayComponent: public Component
{
public:
	OverlayComponent(GameObject* go, std::string const& overlayName);
	~OverlayComponent();

	void hideOverlay(bool hide);
	void setMaterial(std::string const& containerName, std::string const& materialName);
protected:
	OverlayElement* _overlayElement;
};

#endif OVERLAYCOMPONENT_H