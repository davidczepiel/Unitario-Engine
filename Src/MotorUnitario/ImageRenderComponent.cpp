#include "ImageRenderComponent.h"
#include "ComponentIDs.h"
#include "Transform.h"
#include "GameObject.h"

ImageRenderComponent::ImageRenderComponent() : Component(ComponentId::ImageRender), _imageRender(nullptr),_tr(nullptr)
{
	_imageRender = new ImageRender();
}

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject) :Component(ComponentId::ImageRender, gameObject), _imageRender(nullptr),_tr(nullptr)
{
	_imageRender = new ImageRender();
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete _imageRender; _imageRender == nullptr;
	delete _tr; _tr = nullptr;
}

void ImageRenderComponent::start()
{
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());

	_imageRender->setPosition(x, y, z);
}
