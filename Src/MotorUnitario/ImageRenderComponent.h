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
	void setDefaultDimensions(float width, float height);

	/// <summary>
	/// Sets the name of the material to be used for this sprite
	/// </summary>
	/// <param name="name"></param>
	void setMaterialName(const std::string& name);

	/// <summary>
	/// Makes the billboard(sprite) invisible or visible
	/// </summary>
	/// <param name="visible">Whether the objects are to be made visible or invisible</param>
	void setVisible(bool visible);

	/// <summary>
	/// Sets the point which acts as the origin point for the sprite
	/// </summary>
	/// <param name="type">Type of billboardOrigin</param>
	void setBillboardOrigin(ImageRender::BillboardOrigin type);

	/// <summary>
	///Sets the type(orientation) of sprite
	/// </summary>
	/// <param name="type">Type of billboardOrientation</param>
	void setBillboardType(ImageRender::BillboardType type);

	/// <summary>
	///Sets the type(orientation) of rotation of the sprite
	/// </summary>
	/// <param name="type">Type of rotation</param>
	void setBillboardRotationType(ImageRender::BillboardRotationType type);

	/// <summary>
	/// Sets the scale of the sprite
	/// </summary>
	/// <param name="x">New x scale</param>
	/// <param name="y">New y scale</param>
	/// <param name="z">New z scale</param>
	void setPosition(float x, float y, float z);

	/// <summary>
	/// Sets the scale of the sprite
	/// </summary>
	/// <param name="x">New x scale</param>
	/// <param name="y">New y scale</param>
	/// <param name="z">New z scale</param>
	void setScale(float x, float y, float z);

	/// <summary>
	/// Rotate the sprite around an arbitrary axis(x,y,z)
	/// </summary>
	/// <param name="x">x axis</param>
	/// <param name="y">y axis</param>
	/// <param name="z">z axis</param>
	/// <param name="angle">Angle to rotate</param>
	void setRotation(float x, float y, float z, float angle);

private:
	ImageRender* imageRender;
};
#endif // !IMAGERENDERCOMPONENT_H