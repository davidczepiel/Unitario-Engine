#include "RenderObjectComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"

RenderObjectComponent::RenderObjectComponent():Component(ComponentId::RenderObject, nullptr), _renderObject(nullptr),
_transform(nullptr), _meshName("")
{

}

//WIP: add ecs.h to make an ID for this Component
RenderObjectComponent::RenderObjectComponent(GameObject* gameObject, std::string const& meshName) : Component(ComponentId::RenderObject, gameObject), _renderObject(nullptr),
_transform(nullptr),_meshName(meshName)
{
}

RenderObjectComponent::~RenderObjectComponent()
{
}

void RenderObjectComponent::start()
{
	_renderObject = new RenderObject(_meshName, _gameObject->getName());
	_renderObject->init();
}

void RenderObjectComponent::update()
{
	float x = static_cast<float>(_transform->getPosition().getX());
	float y = static_cast<float>(_transform->getPosition().getY());
	float z = static_cast<float>(_transform->getPosition().getZ());
	_renderObject->setPosition(x, y, z);
}
