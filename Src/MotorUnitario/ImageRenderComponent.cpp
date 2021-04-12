#include "ImageRenderComponent.h"
#include "ComponentIDs.h"

ImageRenderComponent::ImageRenderComponent() : Component(ComponentId::ImageRender), imageRender(nullptr)
{
	imageRender = new ImageRender();
}

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject) :Component(ComponentId::ImageRender, gameObject), imageRender(nullptr)
{
	imageRender = new ImageRender();
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete imageRender; imageRender == nullptr;
}