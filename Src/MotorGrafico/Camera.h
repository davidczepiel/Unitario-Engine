#pragma once
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreViewport.h"
class Transform;
class Camera
{

public:
	/** Creates a camera 
	*	@param scn The SceneManager
	*	@param cameraNum An identifier in case the user wants to create multiple cameras 
	 **/
	Camera(Ogre::SceneManager* scn, int cameraNum = 0);
	~Camera();

	/** Sets the near clip plane and the far clip plane
	*	@param near The near clip plane
	*	@param far The far clip plane
	 **/
	void setPlanes(float near = 1, float far = 10000);
	
	/** Sets projection type to ortho or perspective
	*	@param ortho True sets projection type to orthographic, false sets it to perspective
	 **/
	void setProjection(bool ortho);

	/** Sets the field of view angle
	*	@param fovy The new fovY, in degrees (normal values are between 45º and 60º)
	 **/
	void setFovY(float fovy);

	/** Sets the near clip plane dimensions, which will calculate the far clip plane dimensions and set the frustrum
	*	@param left the position of the left side
	*	@param right the position of the right side
	*	@param top the position of the top side
	*	@param bot the position of the bottom side
	 **/
	void setFrustrumDimensions(float left, float right, float top, float bot);

	/** Sets the window dimensions for orthographic perspective (this will recalculate the aspect ratio)
	*	@param w The new window width
	*	@param h The new window height
	 **/
	void setOrthoWindowDimensions(float w, float h);


	/** Sets the viewport dimensions
	*	@param left the viewport new x position 
	*	@param top the viewport new y position
	*	@param w the viewport new width
	*	@param h the viewport new height
	 **/
	void setViewportDimensions(float left, float top, float w, float h);

private:
	Ogre::Camera* _camera;
	Ogre::Viewport* _viewport;
	Ogre::SceneNode* _node;
};

