#pragma once

#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <string>
#include <tuple>

namespace Ogre {
	class SceneNode;
	class Entity;
}

class RenderObject
{
public:
	/// <summary>
	/// Creates a new entity with a mesh
	/// </summary>
	///<param name="meshName">: Name of the object mesh</param>
	RenderObject(std::string const& meshName, std::string const& objectName);

	/// <summary>
	/// Creates a new entity in a position
	/// </summary>
	~RenderObject();

	void init();
	/// <summary>
	/// Rotates the object
	/// </summary>
	///<param name="angle">: Angle to rotate in radians</param>
	///<param name="x">: X axis</param>
	///<param name="y">: Y axis</param>
	///<param name="z">: Z axis</param>
	void rotate(float angle, float x, float y, float z);

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
	/// Sets the object scale
	/// </summary>
	///<param name="x">: X scale</param>
	///<param name="y">: Y scale</param>
	///<param name="z">: Z scale</param>
	void setScale(float x, float y, float z);

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
	/// Set the object rotation
	/// </summary>
	///<param name="x">: X rotation</param>
	///<param name="y">: Y rotation</param>
	///<param name="z">: Z rotation</param>
	void setRotation(float x, float y, float z, float w);

	/// <summary>
	/// Returns the size of the mesh in absolute units
	/// </summary>
	/// <returns></returns>
	const std::tuple<float, float, float>& getMeshSize();

	/// <summary>
	/// Sets alpha of this render Object
	/// </summary>
	void setAlpha(float alpha);

protected:
	Ogre::SceneNode* _objectNode;
	Ogre::Entity* _objectEntity;

	std::string _objectName;
	std::string _meshName;
private:
	std::tuple<float, float, float> _meshSize;
};

#endif //!RENDEROBJECT_H