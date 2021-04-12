#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include <string>

class GameObject;
class Camera;


class CameraComponent : public Component {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	CameraComponent();
	CameraComponent(std::string const& route, GameObject* gameObject);
	CameraComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~CameraComponent();

	/// <summary>
	/// Sets the near clip plane and the far clip plane 
	/// </summary>
	/// <param name="near">The near clip plane</param>
	/// <param name="far">The far clip plane</param>
	 void setPlanes(float near = 1, float far = 10000); 

	/// <summary>
	/// Sets projection type to ortho or perspective
	/// </summary>
	/// <param name="ortho">True sets projection type to orthographic, false sets it to perspective</param>
	 void setProjection(bool ortho); 

	/// <summary>
	/// Sets the field of view angle
	/// </summary>
	/// <param name="fovy">The new fovY, in degrees (normal values are between 45º and 60º)</param>
	 void setFovY(float fovy);

	/// <summary>
	/// Sets the near clip plane dimensions, which will calculate the far clip plane dimensions and set the frustrum
	/// </summary>
	/// <param name="left">The position of the left side</param>
	/// <param name="right">The position of the right side</param>
	/// <param name="top">The position of the top side</param>
	/// <param name="bot">The position of the bottom side</param>
	void setFrustrumDimensions(float left, float right, float top, float bot);
	/// <summary>
	/// Sets the window dimensions for orthographic perspective (this will recalculate the aspect ratio)	/// </summary>
	/// <param name="w">The new window width</param>
	/// <param name="h">The new window height</param>
	void setOrthoWindowDimensions(float w, float h);

	/// <summary>
	/// Sets the viewport dimensions
	/// </summary>
	/// <param name="left">The viewport new x position</param>
	/// <param name="top">The viewport new y position</param>
	/// <param name="w">The viewport new width</param>
	/// <param name="h">The viewport new height</param>
	void setViewportDimensions(float left, float top, float w, float h);
private:
	Camera* _camera;
};
#endif // !CAMERACOMPONENT_H