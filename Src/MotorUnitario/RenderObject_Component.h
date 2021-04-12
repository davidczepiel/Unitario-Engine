#pragma once

#ifndef RENDEROBJECT_COMPONENT_H
#define RENDEROBJECT_COMPONENT_H

#include "Component.h"
#include "MotorGrafico/RenderObject.h"
#include <string>

class Transform;

class RenderObjectComponent : public Component {
public:
	/// <summary>
	/// Constructor of the class
	/// </summary>
	///<param name="meshName">: mesh filename </param>
	RenderObjectComponent(GameObject* gameObject, std::string const& meshName);
	~RenderObjectComponent();
	/// <summary>
	/// Initialize the component
	/// </summary>
	virtual void start() override;
	/// <summary>
	/// Updates the position with Transform Component
	/// </summary>
	virtual void update() override;
	/// <summary>
	/// Set the object material
	/// </summary>
	///<param name="material name">: Name of the material</param>
	inline void setMaterial(std::string const& materialName) { _renderObject->setMaterial(materialName); }

	/// <summary>
	/// Set the object position
	/// </summary>
	///<param name="x">: X position</param>
	///<param name="y">: Y position</param>
	///<param name="z">: Z position</param>
	inline void setPosition(float x, float y, float z) { _renderObject->setPosition(x, y, z); }

	/// <summary>
	/// Rotates the object
	/// </summary>
	///<param name="angle">: Angle to rotate in radians</param>
	///<param name="x">: X axis</param>
	///<param name="y">: Y axis</param>
	///<param name="z">: Z axis</param>
	inline void rotate(float angle, float x, float y, float z) { _renderObject->rotate(angle, x, y, z); }

	/// <summary>
	/// Sets the object scale
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	inline void setScale(float x, float y, float z) { _renderObject->setScale(x, y, z); }

	/// <summary>
	/// Scales the object
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	inline void scale(float x, float y, float z) { _renderObject->scale(x, y, z); }

	/// <summary>
	/// Points the local Z direction of this object at a point in space
	/// </summary>
	///<param name="x">: X axis point</param>
	///<param name="y">: Y axis point</param>
	///<param name="z">: Z axis point</param>
	void lookAt(float x, float y, float z) { _renderObject->scale(x, y, z); }

	/// <summary>
	/// Set the object visibility
	/// </summary>
	///<param name="visible">: is visible</param>
	inline void setVisible(bool visible) { _renderObject->setVisible(visible); }

	/// <summary>
	/// Sets wheter or not this object will cast shadows 
	/// </summary>
	///<param name="castShadows">: cast shadows</param>
	inline void setCastShadows(bool castShadows) { _renderObject->setCastShadows(castShadows); }

	/// <summary>
	/// Sets the distance at which the object is no longer rendered
	/// </summary>
	///<param name="distance">: render distance</param>
	inline void setRenderingDistance(float distance) { _renderObject->setRenderingDistance(distance); }
protected:
private:
	RenderObject* _renderObject;
	Transform* _transform;
	std::string _meshName;
};

#endif //!RENDEROBJECT_COMPONENT_H