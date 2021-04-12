#include "CameraComponent.h"
#include "MotorGrafico/Camera.h"
//#include "ComponentIDs.h"

CameraComponent::CameraComponent() : Component(11), _camera(nullptr)
{
}

CameraComponent::CameraComponent(std::string const& route, GameObject* gameObject) : Component(/*ComponentId::Camera*/1, gameObject), _camera(nullptr)
{
	_camera = new Camera(route);
}

CameraComponent::CameraComponent(GameObject* gameObject) : Component(/*ComponentId::Camera*/1, gameObject), _camera(nullptr)
{
	_camera = new Camera();
}

CameraComponent::~CameraComponent()
{
	delete _camera; _camera == nullptr;
}

void CameraComponent::setPlanes(float near, float far)
{
	_camera->setPlanes(near, far);
}

void CameraComponent::setProjection(bool ortho)
{
	_camera->setProjection(ortho);
}

void CameraComponent::setFovY(float fovy)
{
	_camera->setFovY(fovy);
}

void CameraComponent::setFrustrumDimensions(float left, float right, float top, float bot)
{
	_camera->setFrustrumDimensions(left, right, top, bot);
}

void CameraComponent::setOrthoWindowDimensions(float w, float h)
{
	_camera->setOrthoWindowDimensions(w, h);
}

void CameraComponent::setViewportDimensions(float left, float top, float w, float h)
{
	_camera->setViewportDimensions(left, top, w, h);
}


