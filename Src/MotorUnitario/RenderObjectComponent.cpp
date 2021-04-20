#include "RenderObjectComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"

RenderObjectComponent::RenderObjectComponent():Component(ComponentId::RenderObject, nullptr), _renderObject(nullptr),
_transform(nullptr), _meshName("")
{

}

RenderObjectComponent::RenderObjectComponent(GameObject* gameObject) :Component(ComponentId::RenderObject, gameObject), _renderObject(nullptr),
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

void RenderObjectComponent::awake(luabridge::LuaRef& data)
{
	_meshName = data["MeshName"].cast<std::string>();
	_renderObject = new RenderObject(_meshName, _gameObject->getName());
	rotate(data["RotateAngle"].cast<float>(),data["Rotate"]["X"].cast<float>(), data["Rotate"]["Y"].cast<float>(), data["Rotate"]["Z"].cast<float>());
	setScale(data["Scale"]["X"].cast<float>(), data["Scale"]["Y"].cast<float>(), data["Scale"]["Z"].cast<float>());
	lookAt(data["LookAt"]["X"].cast<float>(), data["LookAt"]["X"].cast<float>(), data["LookAt"]["X"].cast<float>());
	setVisible(data["Visible"].cast<bool>());
	setCastShadows(data["Shadows"].cast<bool>());
	setRenderingDistance(data["RenderingDistance"].cast<float>());
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
