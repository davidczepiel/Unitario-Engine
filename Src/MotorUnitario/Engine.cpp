#include "Engine.h"
//WIP
#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "MotorFisico/PhysxEngine.h"
#include "InputManager.h"
#include "MotorAudio/AudioEngine.h"
#include "ComponentsFactory.h"
#include "ComponentFactory.h"
#include "EngineTime.h"
//DEscomentar
#include "RigidBodyComponent.h"
#include "Transform.h"

std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() : _run(true), _graphicsEngine(nullptr), _inputManager(nullptr)
{
}

void Engine::processEvents()
{
	_inputManager->update();
}

Engine::~Engine()
{
}

Engine* Engine::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new Engine());
	}
	return instance.get();
}

void Engine::tick()
{
	processEvents();
	update();
	//WIP
	fixedUpdate();
	lateUpdate();
	_graphicsEngine->render();
	_audioEngine->update();
	_time->update();
}

void Engine::init()
{
	initFactories();

	_inputManager = InputManager::getInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	setResourcesPath("Assets/prueba.cfg");	// TESTING! This line must be called in game init, before the initialization of Engine
	_graphicsEngine->initRoot();
	_graphicsEngine->initWindow();
	_graphicsEngine->setup();
	/*_physxEngine = PhysxEngine::getPxInstance();
	_physxEngine->init();*/
	_audioEngine = AudioEngine::getInstance();
	_time = EngineTime::getInstance();

	_graphicsEngine->loadScene();
}

void Engine::run()
{
	start();

	while (_run)
	{
		tick();
	}

	shutDown();
}

void Engine::changeScene(const std::string& scene)
{
}

void Engine::stopExecution()
{
	_run = false;
}

void Engine::setResourcesPath(std::string const& resourcesPath)
{
	_graphicsEngine->setResourcePath(resourcesPath);
}

void Engine::start()
{
	for (auto& it : _GOs) {
		it->start();
	}
}

void Engine::fixedUpdate()
{
	for (auto& it : _GOs) {
		it->fixedUpdate();
	}
}

void Engine::update()
{
	for (auto& it : _GOs) {
		it->update();
	}
}

void Engine::lateUpdate()
{
	for (auto& it : _GOs) {
		it->lateUpdate();
	}
}

void Engine::shutDown()
{
	if (_graphicsEngine != nullptr) {
		_graphicsEngine->shutdown();
	}
}

GameObject* Engine::addGameObject()
{
	_GOs.push_back(new GameObject());
	return _GOs.back();
}

void Engine::remGameObject(GameObject* GO)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it) == GO) {
			it = _GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

void Engine::remGameObjectString(const std::string& GOname)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it)->getName() == GOname) {
			delete (*it);
			it = _GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

GameObject* Engine::findGameObject(const std::string& name)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it)->getName() == name) {
			break;
		}
		else
			it++;
	}
	return (it == _GOs.end()) ? (nullptr) : (*it);
}

void Engine::initFactories()
{
	ComponentsFactory::add("ImageRenderer", new ImageRenderComponentFactory());
	ComponentsFactory::add("Light", new LightComponentFactory());
	ComponentsFactory::add("RenderObject", new RenderObjectComponentFactory());
	ComponentsFactory::add("Listener", new ListenerComponentFactory());
	ComponentsFactory::add("AudioSource", new AudioSourceComponentFactory());
	ComponentsFactory::add("RigidBody", new RigidBodyComponentFactory());
	ComponentsFactory::add("BoxCollider", new BoxColliderComponentFactory());
	ComponentsFactory::add("SphereCollider", new SphereColliderComponentFactory());
	ComponentsFactory::add("CapsuleCollider", new CapsuleColliderComponentFactory());
	ComponentsFactory::add("Camera", new CameraComponentFactory());
	ComponentsFactory::add("Animator", new AnimatorComponentFactory());
	ComponentsFactory::add("ParticleSystem", new ParticleSystemComponentFactory());
	ComponentsFactory::add("ButtonComponent", new ButtonComponentFactory());
	ComponentsFactory::add("OverlayComponent", new OverlayComponentFactory());

	// GameObject* go = new GameObject();
	// Component* ir = ComponentsFactory::getComponentByName("ImageRenderer");
	// ir->setGameObject(go);
	// go->addComponent(ir);
	// go->addComponent(ComponentsFactory::getComponentByName("Light"));
	// go->addComponent(ComponentsFactory::getComponentByName("RenderObject"));
	// go->addComponent(ComponentsFactory::getComponentByName("Listener"));
	// go->addComponent(ComponentsFactory::getComponentByName("AudioSource"));
	// go->addComponent(ComponentsFactory::getComponentByName("RigidBody"));
	// go->addComponent(ComponentsFactory::getComponentByName("Collider"));
	// go->addComponent(ComponentsFactory::getComponentByName("Camera"));
	// go->addComponent(ComponentsFactory::getComponentByName("Animator"));
	// go->addComponent(ComponentsFactory::getComponentByName("ParticleSystem"));
}