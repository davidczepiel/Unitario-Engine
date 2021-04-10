#pragma once

#ifndef RENDEROBJECTCOMPONENT_H
#define RENDEROBJECTCOMPONENT_H

#include "Component.h"
#include <string>
//#include "MotorGrafico/RenderObject.h"

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
	inline void setMaterial(std::string const& materialName) {/*_renderObject->setMaterial(materialName);*/ }

	/// <summary>
	/// Set the renderObjects position
	/// </summary>
	///<param name="x">: X position</param>
	///<param name="y">: Y position</param>
	///<param name="z">: Z position</param>
	inline void setPosition(float x, float y, float z) {/*_renderObject->setPosition(x,y,z);*/ }

	/// <summary>
	/// Rotates the object
	/// </summary>
	///<param name="angle">: Angle to rotate in radians</param>
	///<param name="x">: X axis</param>
	///<param name="y">: Y axis</param>
	///<param name="z">: Z axis</param>
	inline void rotate(float angle, float x, float y, float z) {/*_renderObject->rotate(angle,x,y,z);*/ }

	/// <summary>
	/// Sets the object scale
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	inline void setScale(float x, float y, float z) {/*_renderObject->setScale(x,y,z);*/ }

	/// <summary>
	/// Scales the object
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	inline void scale(float x, float y, float z) {/*_renderObject->scale(x,y,z);*/ }

	/// <summary>
	/// Points the renderObject "forward" vector to a specific position
	/// </summary>
	///<param name="x">: X axis point</param>
	///<param name="y">: Y axis point</param>
	///<param name="z">: Z axis point</param>
	inline void lookAt(float x, float y, float z) {/*_renderObject->lookAt(x,y,z);*/ }

	/// <summary>
	/// Set the renderObject visibility
	/// </summary>
	///<param name="visible">: is visible</param>
	inline void setVisible(bool visible) {/*_renderObject->setVisible(visible);*/ }

	/// <summary>
	/// Sets wheter or not this object will cast shadows
	/// </summary>
	///<param name="castShadows">: cast shadows</param>
	inline void setCastShadows(bool castShadows) {/*_renderObject->setCastShadows(castShadows);*/ }

	/// <summary>
	/// Sets the distance at which the object is no longer rendered
	/// </summary>
	///<param name="distance">: render distance</param>
	inline void setRenderingDistance(float distance) {/*_renderObject->setRenderingDistance(distance);*/ }
protected:
	Component* _renderObject;
};

#endif //!RENDEROBJECTCOMPONENT_H