#pragma once

#ifndef RENDEROBJECT_COMPONENT_H
#define RENDEROBJECT_COMPONENT_H

#include "Component.h"
#include <string>

class Transform;
class RenderObject;
class RenderObjectComponent : public Component {
public:
	RenderObjectComponent();

	~RenderObjectComponent();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;
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
	void setMaterial(std::string const& materialName);

	/// <summary>
	/// Set the object position
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
	/// Points the local Z direction of this object at a point in space
	/// </summary>
	///<param name="x">: X axis point</param>
	///<param name="y">: Y axis point</param>
	///<param name="z">: Z axis point</param>
	void lookAt(float x, float y, float z);

	/// <summary>
	/// Set the object visibility
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
	/// <summary>
	/// Sets the alpha value of the object
	/// </summary>
	/// <param name="alpha">The value to use</param>
	void setAlpha(float alpha);

protected:
private:
	/// <summary>
	/// Redefined by child classes called when component is enabled
	/// </summary>
	void onEnable() override;

	/// <summary>
	/// Redefined by child classes called when component is disabled
	/// </summary>
	void onDisable() override;

	RenderObject* _renderObject;
	Transform* _transform;
	std::string _meshName;
};

#endif //!RENDEROBJECT_COMPONENT_H