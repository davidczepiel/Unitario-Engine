#include "RenderObjectComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"
#include "includeLUA.h"

RenderObjectComponent::RenderObjectComponent() :Component(ComponentId::RenderObject, nullptr), _renderObject(nullptr),
_transform(nullptr), _meshName("")
{
}

RenderObjectComponent::~RenderObjectComponent()
{
}

void RenderObjectComponent::awake(luabridge::LuaRef& data)
{
	if (LUAFIELDEXIST(MeshName))
		_meshName = GETLUASTRINGFIELD(MeshName);
	else throw "Mesh doesn't exists\n";
	_renderObject = new RenderObject(_meshName, _gameObject->getName());
	_renderObject->init();

	if (LUAFIELDEXIST(Material))
		setMaterial(GETLUASTRINGFIELD(Material));
	else throw "Material doesn't exists\n ";
	if (LUAFIELDEXIST(Visible))
		setVisible(GETLUAFIELD(Visible, bool));

	if (LUAFIELDEXIST(Shadows))
		setCastShadows(GETLUAFIELD(Shadows, bool));
	float renderDist = 999;
	if (LUAFIELDEXIST(RenderingDistance))
		setRenderingDistance(GETLUAFIELD(RenderingDistance, float));

	if (LUAFIELDEXIST(RotateAngle) && LUAFIELDEXIST(Rotate)) 
	{
		float x, y, z;
		x = y = z=0;
		if (!data["Rotate"]["X"].isNil()) x = data["Rotate"]["X"].cast<float>();
		if (!data["Rotate"]["Y"].isNil()) y = data["Rotate"]["Y"].cast<float>();
		if (!data["Rotate"]["Z"].isNil()) z = data["Rotate"]["Z"].cast<float>();
		rotate(GETLUAFIELD(RotateAngle, float), x, y, z);
	}
}

void RenderObjectComponent::start()
{
	_transform = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	float x = static_cast<float>(_transform->getPosition().getX());
	float y = static_cast<float>(_transform->getPosition().getY());
	float z = static_cast<float>(_transform->getPosition().getZ());
	_renderObject->setPosition(x, y, z);
}

void RenderObjectComponent::update()
{
	float x = static_cast<float>(_transform->getPosition().getX());
	float y = static_cast<float>(_transform->getPosition().getY());
	float z = static_cast<float>(_transform->getPosition().getZ());
	_renderObject->setPosition(x, y, z);

	Vector3 dir = _transform->getForward();
	_renderObject->lookAt(dir.getX(), dir.getY(), dir.getZ());

	Vector3 scale = _transform->getScale();
	_renderObject->setScale(scale.getX(), scale.getY(), scale.getZ());
}
