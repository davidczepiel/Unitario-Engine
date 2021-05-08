#include "Camera.h"
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include "GraphicsEngine.h"
#include "Euler.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

int Camera::_id = 1;

Camera::Camera(const std::string& objectName, int zOrd, float x, float y, float w, float h) : _camera(nullptr), _renderWindow(nullptr), _node(nullptr), _viewport(nullptr), _zOrder(zOrd)
{
	_renderWindow = GraphicsEngine::getInstance()->getRenderWindow();
	Ogre::SceneManager* manager = GraphicsEngine::getInstance()->getSceneManager();
	_camera = manager->createCamera("Camera" + _id);
	_camera->setAutoAspectRatio(true);

	_node = manager->getSceneNode(objectName);
	_node->attachObject(_camera);

	setViewportVisibility(true, x, y, w, h);
	setPlanes();
	_id++;
}

Camera::~Camera()
{
	if (_viewport != nullptr)
		GraphicsEngine::getInstance()->removeViewport(_viewport);
}

void Camera::rotate(float angle, int xAxis, int yAxis, int zAxis)
{
	_node->rotate(Ogre::Vector3(xAxis, yAxis, zAxis), Ogre::Radian(angle));
}

void Camera::lookAt(float x, float y, float z)
{
	_node->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
}

void Camera::pitchDegrees(float degrees, bool world)
{
	if (world) 
		_node->pitch(Ogre::Radian(Ogre::Degree(degrees)), Ogre::Node::TS_WORLD);
	else
		_node->pitch(Ogre::Radian(Ogre::Degree(degrees)));
}

void Camera::pitchRadians(float radians, bool world)
{
	if (world)
		_node->pitch(Ogre::Radian(radians), Ogre::Node::TS_WORLD);
	else
		_node->pitch(Ogre::Radian(radians));
}

void Camera::yawDegrees(float degrees, bool world)
{
	if (world)
		_node->yaw(Ogre::Radian(Ogre::Degree(degrees)), Ogre::Node::TS_WORLD);
	else
		_node->yaw(Ogre::Radian(Ogre::Degree(degrees)));
}

void Camera::yawRadians(float radians, bool world)
{
	if (world)
		_node->yaw(Ogre::Radian(radians), Ogre::Node::TS_WORLD);
	else
		_node->yaw(Ogre::Radian(radians));
}

void Camera::rollDegrees(float degrees, bool world)
{
	if (world)
		_node->roll(Ogre::Radian(Ogre::Degree(degrees)), Ogre::Node::TS_WORLD);
	else
		_node->roll(Ogre::Radian(Ogre::Degree(degrees)));
}

void Camera::rollRadians(float radians, bool world)
{
	if (world)
		_node->roll(Ogre::Radian(radians), Ogre::Node::TS_WORLD);
	else
		_node->roll(Ogre::Radian(radians));
}

void Camera::renderOverlays(bool render)
{
	if (_viewport != nullptr)
		_viewport->setOverlaysEnabled(render);
}

void Camera::setOrientation(float yaw, float pitch, float roll)
{
	//_node->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_PARENT);
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	Ogre::Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	_node->setOrientation(q);
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

const std::tuple<float, float, float>& Camera::getOrientation() {
	Ogre::Euler rot;
	rot.fromQuaternion(_node->getOrientation());
	return std::tuple<float, float, float>(rot.getPitch().valueDegrees(), rot.getYaw().valueDegrees(), rot.getRoll().valueDegrees());
}

void Camera::setViewportVisibility(bool visible, float x, float y, float w, float h)
{
	if (visible) {
		if (_viewport == nullptr) {
			_viewport = GraphicsEngine::getInstance()->setupViewport(_camera, _zOrder, x, y, w, h);
			_camera->setAspectRatio(Ogre::Real(_viewport->getActualWidth()) / Ogre::Real(_viewport->getActualHeight()));
		}
	}
	else {
		if (_viewport != nullptr) {
			GraphicsEngine::getInstance()->removeViewport(_viewport);
			_viewport = nullptr;
		}
	}
}