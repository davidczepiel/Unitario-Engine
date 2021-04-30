#include "ParticleSystem.h"
#include "OgreParticleSystem.h"
#include "GraphicsEngine.h"
#include "OgreSceneManager.h"


ParticleSystem::ParticleSystem() : _pSystem(nullptr), _node(nullptr),_name(), _path()
{
}

ParticleSystem::ParticleSystem(std::string const& path, std::string const& name): _pSystem(nullptr),_node(nullptr), _name(name), _path(path)
{
}

ParticleSystem::~ParticleSystem()
{
	delete _pSystem;
}

void ParticleSystem::init()
{
	_pSystem = GraphicsEngine::getInstance()->getSceneManager()->createParticleSystem(_name, _path);
	_node = GraphicsEngine::getInstance()->getSceneManager()->getSceneNode(_name);
	_node->attachObject(_pSystem);
}

void ParticleSystem::setPosition(double x, double y, double z)
{
	Ogre::Real x_ = static_cast<Ogre::Real>(x);
	Ogre::Real y_ = static_cast<Ogre::Real>(y);
	Ogre::Real z_ = static_cast<Ogre::Real>(z);
	_node->setPosition(Ogre::Vector3(x_, y_, z_));
}


