#include "ParticleSystemComponent.h"
#include "MotorGrafico/ParticleSystem.h"
#include "GameObject.h"
#include "Transform.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* gameObject): Component(3,gameObject), _pSystem(nullptr), _tr(nullptr), _path()
{
}

ParticleSystemComponent::ParticleSystemComponent(GameObject* gameObject, std::string const& path) : Component(3, gameObject), _pSystem(nullptr), _tr(nullptr), _path(path)
{
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	delete _pSystem;
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
