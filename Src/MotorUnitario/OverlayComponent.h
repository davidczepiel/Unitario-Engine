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
	/// <summary>
	/// Class constructor with GameObject
	/// </summary>
	/// <param name="go"> Game Object </param>
	OverlayComponent();
	OverlayComponent(GameObject* go);

	/// <summary>
	/// Class constructor with class params
	/// </summary>
	/// <param name="go"> Game Object</param>
	/// <param name="overlayName"> Overlay name</param>
	OverlayComponent(GameObject* go, std::string const& overlayName);
	~OverlayComponent();

	void start();

	/// <summary>
	/// Hides the overlay
	/// </summary>
	/// <param name="hide"></param>
	void hideOverlay(bool hide);

	/// <summary>
	/// Sets the overlay material
	/// </summary>
	/// <param name="containerName"></param>
	/// <param name="materialName"></param>
	void setMaterial(std::string const& containerName, std::string const& materialName);

	/// <summary>
	/// Sets the overlay name (before start is called)
	/// </summary>
	/// <param name="overlayName"></param>
	inline void setOverlayName(std::string const& overlayName) { _overlayName = overlayName; }
protected:
	//Overlay name
	std::string _overlayName;
	//Pointer to overlay element
	OverlayElement* _overlayElement;
};

#endif OVERLAYCOMPONENT_H