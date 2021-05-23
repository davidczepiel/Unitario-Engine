#include "ParticleSystemComponent.h"
#include "MotorGrafico/ParticleSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"
#include "includeLUA.h"
#include "Exceptions.h"

ParticleSystemComponent::ParticleSystemComponent() : Component(ComponentId::ParticleSystem), _pSystem(nullptr), _tr(nullptr), _path()
{
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	delete _pSystem;
}

void ParticleSystemComponent::awake(luabridge::LuaRef& data)
{
	try {
		if (LUAFIELDEXIST(Path))
		{
			_path = GETLUASTRINGFIELD(Path);
			_pSystem = new ParticleSystem(_path, _gameObject->getName());
		}
		_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	}
	catch (...) {
		throw SourcePathException("The path of the PartycleSystem or the conteiner of the game object " + _gameObject->getName() + " is wrong");
	}	
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