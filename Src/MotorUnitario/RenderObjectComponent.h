#pragma once

#ifndef RENDEROBJECTCOMPONENT_H
#define RENDEROBJECTCOMPONENT_H

#include "Component.h"
#include <string>

//class RenderObject

class RenderObjectComponent : public Component
{
public:
	/// <summary>
	/// Creates a new renderObject for an entity
	/// </summary>
	///<param name="meshName">: Name of the object mesh</param>
	///<param name="gameObject">: GameObject which will contain this component</param>
	RenderObjectComponent(std::string const& meshName, GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~RenderObjectComponent();

	/// <summary>
	/// Set the object material
	/// </summary>
	///<param name="material name">: Name of the material</param>
	void setMaterial(std::string const& materialName);

	/// <summary>
	/// Set the renderObjects position
	/// </summary>
	///<param name="x">: X position</param>
	///<param name="y">: Y position</param>
	///<param name="z">: Z position</param>
	void setPosition(float x, float y, float z);

	/// <summary>
	/// Rotates the object
	/// </summary>
	///<param name="angle">: Angle to rotate in radians</param>
	///<param name="x">: X axis</param>
	///<param name="y">: Y axis</param>
	///<param name="z">: Z axis</param>
	void rotate(float angle, float x, float y, float z);

	/// <summary>
	/// Sets the object scale
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	void setScale(float x, float y, float z);

	/// <summary>
	/// Scales the object
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	void scale(float x, float y, float z);

	/// <summary>
	/// Points the renderObject "forward" vector to a specific position
	/// </summary>
	///<param name="x">: X axis point</param>
	///<param name="y">: Y axis point</param>
	///<param name="z">: Z axis point</param>
	void lookAt(float x, float y, float z);

	/// <summary>
	/// Set the renderObject visibility
	/// </summary>
	///<param name="visible">: is visible</param>
	void setVisible(bool visible);

	/// <summary>
	/// Sets wheter or not this object will cast shadows
	/// </summary>
	///<param name="castShadows">: cast shadows</param>
	void setCastShadows(bool castShadows);

	/// <summary>
	/// Sets the distance at which the object is no longer rendered
	/// </summary>
	///<param name="distance">: render distance</param>
	void setRenderingDistance(float distance);
protected:
	Component* _renderObject;
};

#endif //!RENDEROBJECTCOMPONENT_H