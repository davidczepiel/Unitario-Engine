#pragma once
#ifndef IMAGERENDERCOMPONENT_H
#define IMAGERENDERCOMPONENT_H

#include "MotorGrafico/ImageRender.h"
#include "Component.h"

class GameObject;

class ImageRenderComponent : public Component {
public:
	ImageRenderComponent();
	ImageRenderComponent(GameObject* gameObject);
	~ImageRenderComponent();

	/// <summary>
	/// Sets the dimensions(width and height) of the sprite
	/// </summary>
	/// <param name="width">New width</param>
	/// <param name="height">New height</param>
	inline void setDefaultDimensions(float width, float height) { imageRender->setDefaultDimensions(width, height); }

	/// <summary>
	/// Sets the name of the material to be used for this sprite
	/// </summary>
	/// <param name="name"></param>
	inline void setMaterialName(const std::string& name) { imageRender->setMaterialName(name); }

	/// <summary>
	/// Makes the billboard(sprite) invisible or visible 
	/// </summary>
	/// <param name="visible">Whether the objects are to be made visible or invisible</param>
	inline void setVisible(bool visible) { imageRender->setVisible(visible); }

	/// <summary>
	/// Sets the point which acts as the origin point for the sprite
	/// </summary>
	/// <param name="type">Type of billboardOrigin</param>
	inline void setBillboardOrigin(ImageRender::BillboardOrigin type) { imageRender->setBillboardOrigin(type); }

	/// <summary>
	///Sets the type(orientation) of sprite
	/// </summary>
	/// <param name="type">Type of billboardOrientation</param>
	inline void setBillboardType(ImageRender::BillboardType type) { imageRender->setBillboardType(type); }

	/// <summary>
	///Sets the type(orientation) of rotation of the sprite
	/// </summary>
	/// <param name="type">Type of rotation</param>
	inline void setBillboardRotationType(ImageRender::BillboardRotationType type) { imageRender->setBillboardRotationType(type); }

	/// <summary>
	/// Sets the scale of the sprite 
	/// </summary>
	/// <param name="x">New x scale</param>
	/// <param name="y">New y scale</param>
	/// <param name="z">New z scale</param>
	inline void setPosition(float x, float y, float z) { imageRender->setPosition(x, y, z); }

	/// <summary>
	/// Sets the scale of the sprite 
	/// </summary>
	/// <param name="x">New x scale</param>
	/// <param name="y">New y scale</param>
	/// <param name="z">New z scale</param>
	inline void setScale(float x, float y, float z) { imageRender->setScale(x, y, z); }

	/// <summary>
	/// Rotate the sprite around an arbitrary axis(x,y,z) 
	/// </summary>
	/// <param name="x">x axis</param>
	/// <param name="y">y axis</param>
	/// <param name="z">z axis</param>
	/// <param name="angle">Angle to rotate</param>
	inline void setRotation(float x, float y, float z,float angle) { imageRender->setRotation(x, y, z, angle); }

private:
	ImageRender* imageRender;
};
#endif // !IMAGERENDERCOMPONENT_H