#pragma once
#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#include "Component.h"
#include <string>

class OverlayElement;

class ButtonComponent: public Component
{
	/// <summary>
	/// Static function that is called when user clicks on the button
	/// </summary>
	using CallBackOnClick = void(void*);
public:
	/// <summary>
	/// Default constructor of the class
	/// </summary>
	ButtonComponent();
	ButtonComponent(GameObject* gO);
	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="callback">: function that is called when user clicks on the button</param>
	/// <param name="overlayName">: name in .overlay script that is used in Overlay Element load</param>
	/// <param name="containerName">: name in .overlay script to the child of the container </param>
	/// <param name="defaultMaterial">: material name in .material script used to default state button </param>
	/// <param name="passingMaterial">: material name in .material script used to hover state button </param>
	/// <param name="pressMaterial">: material name in .material script used to press state button  </param>
	ButtonComponent(GameObject* gO, CallBackOnClick* callback, std::string const& overlayName, std::string const& containerName,
		std::string const& defaultMaterial, std::string const& hoverMaterial, std::string const& pressMaterial, void* callbackParam = nullptr);
	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ButtonComponent();
	/// <summary>
	/// Inicialize Overlay Element
	/// </summary>
	virtual void start() override;
	/// <summary>
	/// Checks the mouse position with the button position and size and change the state of the button.
	/// </summary>
	virtual void update() override;

	/// <summary>
	/// Hide or show the button graphically. Also stop being active.
	/// </summary>
	/// <param name="show">: true = show, false = hide</param>
	void hideShowButton(bool show);

	/// <summary>
	/// Sets the button active or not. 
	/// </summary>
	inline void setActive(bool active) { _active = active; }

	/// <summary>
	/// Sets the function that is called when user clicks on the button
	/// </summary>
	/// <param name="c">: static callback function</param>
	inline void setCallBack(CallBackOnClick* c) { _callback = c; }

	/// <summary>
	/// Sets the callback parameter
	/// </summary>
	/// <param name="param">: any type</param>
	inline void setCallBackParam(void* param) { _callbackParam = param; }

	/// <summary>
	/// Sets the overlay name
	/// </summary>
	/// <param name="overlayName">: name in .overlay script that is used in Overlay Element load</param>
	inline void setOverlayName(std::string const& overlayName) { _overlayName = overlayName; }

	/// <summary>
	/// Sets the default name material
	/// </summary>
	/// <param name="defaultMaterial">: material name in .material script used to default state button </param>
	inline void setDeafultName(std::string const& defaultMaterial) { _defaultMaterial = defaultMaterial; }

	/// <summary>
	/// Sets the hover name material
	/// </summary>
	/// <param name="hoverMaterial">: material name in .material script used to hover state button </param>
	inline void setHoverName(std::string const& hoverMaterial) { _hoverMaterial = hoverMaterial; }
	/// <summary>
	/// Sets the press name material
	/// </summary>
	/// <param name="pressMaterial">: material name in .material script used to press state button </param>
	inline void setPressName(std::string const& pressMaterial) { _pressMaterial = pressMaterial; }

private:
	OverlayElement* _button;
	CallBackOnClick* _callback;
	void* _callbackParam;
	std::string _overlayName;
	std::string _containerName;
	std::string _defaultMaterial;
	std::string _hoverMaterial;
	std::string _pressMaterial;
	bool _active;
};

#endif BUTTONCOMPONENT_H