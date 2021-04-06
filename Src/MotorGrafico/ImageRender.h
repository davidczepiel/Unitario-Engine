#pragma once
#ifndef IMAGERENDER_H
#define IMAGERENDER_H

#include <string>

namespace Ogre
{
	class SceneNode;
	class BillboardSet;
};

class ImageRender {
public:

	//Here we have all the types of origins of a billboard
	enum BillboardOrigin {
		BBO_TOP_LEFT=0, BBO_TOP_CENTER=1, BBO_TOP_RIGHT=2, BBO_CENTER_LEFT=3, BBO_CENTER=4, 
		BBO_CENTER_RIGHT=5, BBO_BOTTOM_LEFT=6, BBO_BOTTOM_CENTER=7, BBO_BOTTOM_RIGHT=8				
	};

	//Here we have all the orientation types of a billboard
	enum BillboardType {
		//Standard point billboard (default), always faces the camera completely and is always upright
		BBT_POINT=0, 
		//Billboards are oriented around a shared direction vector(used as Y axis) and only rotate around this to face the camera
		BBT_ORIENTED_COMMON=1,
		//Billboards are oriented around their own direction vector (their own Y axis) and only rotate around this to face the camera
		BBT_ORIENTED_SELF=2,
		//Billboards are perpendicular to a shared direction vector (used as Z axis, the facing direction) and X, Y axis are determined by a shared up-vertor
		BBT_PERPENDICULAR_COMMON=3,
		//Billboards are perpendicular to their own direction vector (their own Z axis, the facing direction) and X, Y axis are determined by a shared up-vertor
		BBT_PERPENDICULAR_SELF=4
	};

	ImageRender();
	~ImageRender();

	/// <summary>
	/// Sets the dimensions(width and height) of the billboards in the billboardSet
	/// </summary>
	/// <param name="width">New width</param>
	/// <param name="height">New height</param>
	void setDefaultDimensions(float width, float height);

	/// <summary>
	/// Sets the name of the material to be used for this billboardSet
	/// </summary>
	/// <param name="name"></param>
	void setMaterialName(const std::string& name);

	/// <summary>
	/// Makes the billboardSet attached to this node become invisible or visible 
	/// </summary>
	/// <param name="visible">Whether the objects are to be made visible or invisible</param>
	void setVisible(bool visible);

	/// <summary>
	/// Sets the point which acts as the origin point for all billboards in this set
	/// </summary>
	/// <param name="type">Type of billboardOrigin</param>
	void setBillboardOrigin(BillboardOrigin type);

	/// <summary>
	///Sets the type(orientation) of billboard to use in this set
	/// </summary>
	/// <param name="type">Type of billboardOrientation</param>
	void setBillboardType(BillboardType type);

private:

	Ogre::SceneNode* _billboardSetNode;
	Ogre::BillboardSet* _billboardSet;	
};
#endif // !IMAGERENDER_H


