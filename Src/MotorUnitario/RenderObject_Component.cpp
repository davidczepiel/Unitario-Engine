#include "RenderObject_Component.h"

//WIP: add ecs.h to make an ID for this Component
RenderObjectComponent::RenderObjectComponent(GameObject* gameObject, std::string const& meshName) : Component(3, gameObject), _renderObject(nullptr)
{
	//WIP : Initialize RenderObject
}

RenderObjectComponent::~RenderObjectComponent()
{
}
