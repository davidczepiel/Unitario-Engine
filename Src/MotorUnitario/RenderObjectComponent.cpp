#include "RenderObjectComponent.h"

RenderObjectComponent::RenderObjectComponent() : Component(1),_renderObject(nullptr)
{
}

RenderObjectComponent::RenderObjectComponent(std::string const& meshName, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _renderObject(nullptr)
{
	//_renderObject = new RenderObject(meshName);
}

RenderObjectComponent::~RenderObjectComponent()
{
	delete _renderObject; _renderObject = nullptr;
}

void RenderObjectComponent::setMaterial(std::string const& materialName) {
	/*_renderObject->setMaterial(materialName);*/
}

void RenderObjectComponent::setPosition(float x, float y, float z) {
	/*_renderObject->setPosition(x,y,z);*/
}

void RenderObjectComponent::rotate(float angle, float x, float y, float z) {
	/*_renderObject->rotate(angle,x,y,z);*/
}

void RenderObjectComponent::setScale(float x, float y, float z) {
	/*_renderObject->setScale(x,y,z);*/
}

void RenderObjectComponent::scale(float x, float y, float z) {
	/*_renderObject->scale(x,y,z);*/
}

void RenderObjectComponent::lookAt(float x, float y, float z) {
	/*_renderObject->lookAt(x,y,z);*/
}

void RenderObjectComponent::setVisible(bool visible) {
	/*_renderObject->setVisible(visible);*/
}

void RenderObjectComponent::setCastShadows(bool castShadows) {
	/*_renderObject->setCastShadows(castShadows);*/
}

void RenderObjectComponent::setRenderingDistance(float distance) {
	/*_renderObject->setRenderingDistance(distance);*/
}