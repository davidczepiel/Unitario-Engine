#include "Camera.h"
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>

Camera::Camera(Ogre::SceneManager* scn, Ogre::RenderWindow* rWin, int cameraNum) :_camera(nullptr), _renderWindow(rWin), _node(nullptr),
_viewport(nullptr)
{
	_camera = scn->createCamera("camera" + cameraNum);
	_camera->setAutoAspectRatio(true);
	_node = scn->getRootSceneNode()->createChildSceneNode(_camera->getName());
	_node->attachObject(_camera);

	_viewport = rWin->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0.98, 0.972, 0.949));
	_viewport->setOverlaysEnabled(true);
}

Camera::Camera() :_camera(nullptr), _renderWindow(nullptr), _node(nullptr), _viewport(nullptr)
{
}

Camera::Camera(std::string path) : _camera(nullptr), _renderWindow(nullptr), _node(nullptr), _viewport(nullptr)
{
}

Camera::~Camera()
{
	delete _camera;
	delete _node;
}

void Camera::lookAt(float x, float y, float z)
{
	_node->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
}

void Camera::pitchDegrees(float degrees)
{
	_node->pitch(Ogre::Radian(Ogre::Degree(degrees)));
}

void Camera::pitchRadians(float radians)
{
	_node->pitch(Ogre::Radian(radians));
}

void Camera::yawDegrees(float degrees)
{
	_node->yaw(Ogre::Radian(Ogre::Degree(degrees)));
}

void Camera::yawRadians(float radians)
{
	_node->yaw(Ogre::Radian(radians));
}

void Camera::rollDegrees(float degrees)
{
	_node->roll(Ogre::Radian(Ogre::Degree(degrees)));
}

void Camera::rollRadians(float radians)
{
	_node->roll(Ogre::Radian(radians));
}

void Camera::setOrientation(float w, float x, float y, float z)
{
	_node->setOrientation(w, x, y, z);
}

void Camera::setOrientation(Ogre::Quaternion orientation)
{
	_node->setOrientation(orientation);
}

void Camera::setPosition(float x, float y, float z)
{
	_node->setPosition(Ogre::Vector3(x, y, z));
}

void Camera::translate(float x, float y, float z)
{
	_node->translate(x, y, z, Ogre::Node::TS_WORLD);
}

void Camera::setPlanes(float near, float far)
{
	_camera->setNearClipDistance(near);
	_camera->setFarClipDistance(far);
}

void Camera::setProjection(bool ortho)
{
	if (ortho)
		_camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	else _camera->setProjectionType(Ogre::PT_PERSPECTIVE);
}
void Camera::setFovY(float fovy)
{
	Ogre::Radian fovyInRadians(Ogre::Math::DegreesToRadians(fovy));
	_camera->setFOVy(fovyInRadians);
}
void Camera::setFrustrumDimensions(float left, float right, float top, float bot)
{
	_camera->setFrustumExtents(left, right, top, bot);
}

void Camera::setOrthoWindowDimensions(float w, float h)
{
	if (_camera->getProjectionType() == Ogre::PT_ORTHOGRAPHIC)
		_camera->setOrthoWindow(w, h);
}

void Camera::setViewportDimensions(float left, float top, float w, float h)
{
	_viewport->setDimensions(left, top, w, h);
}

Ogre::Viewport* Camera::getViewPort()
{
	return _viewport;
}