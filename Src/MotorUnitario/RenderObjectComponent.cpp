#include "RenderObjectComponent.h"

RenderObjectComponent::RenderObjectComponent(std::string const& meshName, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _renderObject(nullptr)
{
	//_renderObject = new RenderObject(meshName);
}

RenderObjectComponent::~RenderObjectComponent()
{
	delete _renderObject; _renderObject = nullptr;
}