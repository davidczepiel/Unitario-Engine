#include "Engine.h"
//WIP
#include "MotorGrafico/main.h"
#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "InputManager.h"
#include "MotorAudio/AudioEngine.h"
#include "ComponentsFactory.h"
#include "ComponentFactory.h"
#include "Time.h"

Engine* Engine::_instance = nullptr;

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
	if (_instance == nullptr) {
		_instance = new Engine();
	}
	return _instance;
}

void Engine::tick()
{
	processEvents();
	update();
	//WIP
	fixedUpdate();
	lateUpdate();
	_graphicsEngine->render();
	_time->update();
}

void Engine::init()
{
	_inputManager = InputManager::getInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	_audioEngine = AudioEngine::getInstance();
	_time = Time::getInstance();
	_graphicsEngine->initRoot();
	_graphicsEngine->initWindow();
	_graphicsEngine->setup();

	initFactories();
}

void Engine::run()
{
	start();
	while (_run)
	{
		tick();
	}
}

void Engine::changeScene(const std::string& scene)
{
}

void Engine::stopExecution()
{
	_run = false;
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
	_audioEngine->update();
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

void Engine::freeEnginesResources() {
}

void Engine::initFactories()
{
	ComponentsFactory::add("ImageRenderer", new ImageRenderComponentFactory());
	ComponentsFactory::add("Light", new LightComponentFactory());
	ComponentsFactory::add("RenderObject", new RenderObjectComponentFactory());
	ComponentsFactory::add("Listener", new ListenerComponentFactory());
	ComponentsFactory::add("AudioSource", new AudioSourceComponentFactory());
	ComponentsFactory::add("RigidBody", new RigidBodyComponentFactory());
	ComponentsFactory::add("Collider", new ColliderComponentFactory());
	ComponentsFactory::add("Camera", new CameraComponentFactory());
	ComponentsFactory::add("Animator", new AnimatorComponentFactory());
	ComponentsFactory::add("ParticleSystem", new ParticleSystemComponentFactory());

	GameObject* go = new GameObject();
	Component* ir = ComponentsFactory::getComponentByName("ImageRenderer");
	ir->setGameObject(go);
	go->addComponent(ir);
	go->addComponent(ComponentsFactory::getComponentByName("Light"));
	go->addComponent(ComponentsFactory::getComponentByName("RenderObject"));
	go->addComponent(ComponentsFactory::getComponentByName("Listener"));
	go->addComponent(ComponentsFactory::getComponentByName("AudioSource"));
	go->addComponent(ComponentsFactory::getComponentByName("RigidBody"));
	go->addComponent(ComponentsFactory::getComponentByName("Collider"));
	go->addComponent(ComponentsFactory::getComponentByName("Camera"));
	go->addComponent(ComponentsFactory::getComponentByName("Animator"));
	go->addComponent(ComponentsFactory::getComponentByName("ParticleSystem"));
}
