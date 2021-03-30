#pragma once

#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <OgreSceneNode.h>
#include <OgreEntity.h>

class RenderObject
{
public:
	/// <summary>
	/// Class constructor
	/// </summary>
	///<param name="meshName">: Name of the object mesh</param>
	RenderObject(std::string meshName);
	~RenderObject();

	/// <summary>
	/// Set the object material
	/// </summary>
	///<param name="material name">: Name of the material</param>
	void setMaterial(std::string materialName);

	/// <summary>
	/// Set the object position
	/// </summary>
	///<param name="x">: X position</param>
	///<param name="y">: Y position</param>
	///<param name="z">: Z position</param>
	void setPosition(float x, float y, float z);

	/// <summary>
	/// Set the object orientation
	/// </summary>
	///<param name="angle">: Angle to rotate in radians</param>
	///<param name="x">: X axis</param>
	///<param name="y">: Y axis</param>
	///<param name="z">: Z axis</param>
	void setOrientation(float angle, float x, float y, float z);

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
protected:
	Ogre::SceneNode* objectNode;
	Ogre::Entity* objectEntity;
private:
};

#endif /*RENDEROBJECT_H*/