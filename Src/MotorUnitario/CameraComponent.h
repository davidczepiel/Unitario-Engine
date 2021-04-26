#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "Vector3.h"
#include <string>

class GameObject;
class Camera;
class Transform;

class CameraComponent : public Component {
public:

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Contructor of the class
	/// </summary>
	CameraComponent();

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~CameraComponent();

	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start() override;
	/// <summary>
	/// Update the component
	/// </summary>
	virtual void update() override;
	/// <summary>
	/// Called each frame after update.
	/// </summary>
	virtual void lateUpdate() override;

	/// <summary>
/// Redirects the Z axis of the camera so that it points to a specific world position
/// </summary>
/// <param name="x">The worlds x position that the camera will point at</param>
/// <param name="y">The worlds y position that the camera will point at</param>
/// <param name="z">The worlds z position that the camera will point at</param>
	void lookAt(float x, float y, float z);

	/// <summary>
	/// Rotates the camera node using its X axis
	/// </summary>
	/// <param name="degrees">Amounts of degrees to rotate</param>
	void pitchDegrees(float degrees);

	/// <summary>
	/// Rotates the camera node using its X axis
	/// </summary>
	/// <param name="radians">Amounts of radians to rotate</param>
	void pitchRadians(float radians);

	/// <summary>
	/// Rotates the camera node using its Y axis
	/// </summary>
	/// <param name="degrees">Amounts of degrees to rotate</param>
	void yawDegrees(float degrees);

	/// <summary>
	/// Rotates the camera node using its Y axis
	/// </summary>
	/// <param name="amount">Amounts of units to rotate</param>
	void yawRadians(float amount);

	/// <summary>
	/// Rotates the camera node using its Z axis
	/// </summary>
	/// <param name="degrees">Amounts of degrees to rotate</param>
	void rollDegrees(float degrees);

	/// <summary>
	/// Rotates the camera node using its Z axis
	/// </summary>
	/// <param name="radians">Amounts of radians to rotate</param>
	void rollRadians(float radians);

	/// <summary>
	/// Redirects the Z axis of the camera so that it points to a specific world position
	/// </summary>
	/// <param name="x">The worlds x position that the camera will point at</param>
	/// <param name="y">The worlds y position that the camera will point at</param>
	/// <param name="z">The worlds z position that the camera will point at</param>
	void setOrientation(float x, float y, float z);

	/// <summary>
	/// Adjusts the cameras node so that it is oriented given a Quarternion
	/// </summary>
	/// <param name="orientation">Quaternion wich specifies the camera new orientation </param>
	//void setOrientation(Ogre::Quaternion orientation);

	/// <summary>
	/// Sets the camera position to a specified location
	/// </summary>
	/// <param name="x">The camera new x position</param>
	/// <param name="y">The camera new y position</param>
	/// <param name="z">The camera new z position </param>
	void setPosition(float x, float y, float z);

	/// <summary>
	/// Moves the camera from its position an specified amount of units in each axis
	/// </summary>
	/// <param name="x">The camera movement on the x axis</param>
	/// <param name="y">The camera movement on the y axis</param>
	/// <param name="z">The camera movement on the z axis</param>
	void translate(float x, float y, float z);

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
	/// Creates a new viewport if visible is True and removes it if Visible is false
	/// </summary>
	/// <param name="visible"> Visibilit of the viewport </param>
	/// <param name="x">The viewport new x position</param>
	/// <param name="y">The viewport new y position</param>
	/// <param name="w">The viewport new width</param>
	/// <param name="h">The viewport new height</param>
	void setViewportVisibility(bool visible, float x = 0., float y = 0., float w = 1., float h = 1.);

	/// <summary>
	/// Sets the viewport dimensions
	/// </summary>
	/// <param name="left">The viewport new x position</param>
	/// <param name="top">The viewport new y position</param>
	/// <param name="w">The viewport new width</param>
	/// <param name="h">The viewport new height</param>
	void setViewportDimensions(float left, float top, float w, float h);

	/// <summary>
	/// gets the camera orientation in degrees
	/// </summary>
	/// <returns>The camera orientation</returns>
	const Vector3& getOrientation();
	
private:
	Camera* _camera;
	Transform* _tr;
};

ADD_COMPONENT(CameraComponent)

#endif // !CAMERACOMPONENT_H
