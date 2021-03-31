#pragma once
#ifndef IMAGERENDERCOMPONENT_H
#define IMAGERENDERCOMPONENT_H

#include "MotorGrafico/ImageRender.h"
#include "Component.h"

class GameObject;

class ImageRenderComponent : public Component {
public:
	ImageRenderComponent(GameObject* gameObject);
	~ImageRenderComponent();

	/// <summary>
	/// Sets the dimensions(width and height) of the billboard(sprite)
	/// </summary>
	/// <param name="width">New width</param>
	/// <param name="height">New height</param>
	inline void setDefaultDimensions(float width, float height) { imageRender->setDefaultDimensions(width, height); }

	/// <summary>
	/// Sets the name of the material to be used for this billboard(sprite)
	/// </summary>
	/// <param name="name"></param>
	inline void setMaterialName(const std::string& name) { imageRender->setMaterialName(name); }

	/// <summary>
	/// Makes the billboard(sprite) invisible or visible 
	/// </summary>
	/// <param name="visible">Whether the objects are to be made visible or invisible</param>
	inline void setVisible(bool visible) { imageRender->setVisible(visible); }

	/// <summary>
	/// Sets the point which acts as the origin point for the billboard(sprite)
	/// </summary>
	/// <param name="type">Type of billboardOrigin</param>
	inline void setBillboardOrigin(ImageRender::BillboardOrigin type) { imageRender->setBillboardOrigin(type); }

	/// <summary>
	///Sets the type(orientation) of billboard(sprite)
	/// </summary>
	/// <param name="type">Type of billboardOrientation</param>
	inline void setBillboardType(ImageRender::BillboardType type) { imageRender->setBillboardType(type); }

private:
	ImageRender* imageRender;
};
#endif // !IMAGERENDERCOMPONENT_H