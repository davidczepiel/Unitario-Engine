#include "ParticleSystemComponent.h"
#include "MotorGrafico/ParticleSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"

//ADD_COMPONENT(ParticleSystemComponent)

ParticleSystemComponent::ParticleSystemComponent() : Component(ComponentId::ParticleSystem), _pSystem(nullptr), _tr(nullptr), _path()
{
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	delete _pSystem;
}

void ParticleSystemComponent::awake(luabridge::LuaRef& data)
{
	//_gameObject->getComponent(ComponentId::ComponentId::Transform)->awake(data);
	_path = data["Path"].cast<std::string>();
}

void ParticleSystemComponent::start()
{
	_pSystem->init();
	_pSystem->setName(_gameObject->getName());
}

void ParticleSystemComponent::update()
{
	_pSystem->setPosition(_tr->getPosition().getX(), _tr->getPosition().getY(), _tr->getPosition().getZ());
}

void ParticleSystemComponent::setPath(std::string const& path)
{
	_pSystem->setPath(path);
}
