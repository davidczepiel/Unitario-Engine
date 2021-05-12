#pragma once
#ifndef OVERLAYELEMENTMNGRMU_H
#define OVERLAYELEMENTMNGRMU_H

#include <string>

class OgreOverlayElement;

class OverlayElementMngr
{
public:
	/// <summary>
	/// Class constructor with GameObject
	/// </summary>
	/// <param name="go"> Game Object </param>
	OverlayElementMngr(std::string elementName);

	~OverlayElementMngr();

	/// <summary>
	/// Sets the overlay element position (1.0 = top/left)
	/// </summary>
	void setPosition(float left, float top);

	/// <summary>
	/// Hides the overlay
	/// </summary>
	/// <param name="hide"></param>
	void setEnabled(bool hide);

	/// <summary>
	/// Sets the overlay element width
	/// </summary>
	void setWidth(float w);

	/// <summary>
	/// Sets the overlay element height
	/// </summary>
	void setHeight(float h);

	/// <summary>
	/// Sets the overlay material
	/// </summary>
	/// <param name="containerName"></param>
	/// <param name="materialName"></param>
	void setMaterial(std::string const& materialName);
protected:
	OgreOverlayElement* _overlayElement;
};



#endif OVERLAYELEMENTMNGRMU_H