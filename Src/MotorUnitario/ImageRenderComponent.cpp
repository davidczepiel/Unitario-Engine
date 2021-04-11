#include "ImageRenderComponent.h"
//#include "ComponentIDs.h"

ImageRenderComponent::ImageRenderComponent() : Component(2), imageRender(nullptr)
{
	imageRender = new ImageRender();
}

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject) :Component(/*ComponentId::ImageRender*/1, gameObject), imageRender(nullptr)
{
	imageRender = new ImageRender();
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete imageRender; imageRender == nullptr;
}

void ImageRenderComponent::setDefaultDimensions(float width, float height) {
	imageRender->setDefaultDimensions(width, height);
}

void ImageRenderComponent::setMaterialName(const std::string& name) {
	imageRender->setMaterialName(name);
}

void ImageRenderComponent::setVisible(bool visible) {
	imageRender->setVisible(visible);
}

void ImageRenderComponent::setBillboardOrigin(ImageRender::BillboardOrigin type) {
	imageRender->setBillboardOrigin(type);
}

void ImageRenderComponent::setBillboardType(ImageRender::BillboardType type) {
	imageRender->setBillboardType(type);
}

void ImageRenderComponent::setBillboardRotationType(ImageRender::BillboardRotationType type) {
	imageRender->setBillboardRotationType(type);
}

void ImageRenderComponent::setPosition(float x, float y, float z) {
	imageRender->setPosition(x, y, z);
}

void ImageRenderComponent::setScale(float x, float y, float z) {
	imageRender->setScale(x, y, z);
}

void ImageRenderComponent::setRotation(float x, float y, float z, float angle) {
	imageRender->setRotation(x, y, z, angle);
}