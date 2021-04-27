#include "Engine.h"

#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "MotorFisico/PhysxEngine.h"
#include "InputManager.h"
#include "MotorAudio/AudioEngine.h"
#include "EngineTime.h"
#include "LuaParser.h"
#include "Logger.h"

#include "ComponentsFactory.h"
#include "ComponentFactory.h"

std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() : _run(true), _graphicsEngine(nullptr), _inputManager(nullptr), alredyInitialized(false)
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
	return instance.get();
}

void Engine::CreateInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new Engine());
	}
	else {
		Logger::getInstance()->log("Trying to create Engine instance and it already exist", Logger::Level::WARN);
	}
}

void Engine::tick()
{
	processEvents();
	fixedUpdate();
	update();
	lateUpdate();
	_graphicsEngine->render();
	_audioEngine->update();
	_physxEngine->update(_time->deltaTime());
	_time->update();
}

bool Engine::init(std::string const& resourcesPath)
{
	if (alredyInitialized) {
		Logger::getInstance()->log("Engine class is already initialized", Logger::Level::WARN);
		return false;
	}

	_inputManager = InputManager::getInstance();
	GraphicsEngine::CreateInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	_graphicsEngine->setResourcePath(resourcesPath);
	if (!_graphicsEngine->initializeRenderEngine()) {
		Logger::getInstance()->log("Graphics Engine init error", Logger::Level::ERROR);
		throw "Graphics Engine init error";
	}
	PhysxEngine::CreateInstance();
	_physxEngine = PhysxEngine::getPxInstance();
	_physxEngine->init();
	AudioEngine::CreateInstance();
	_audioEngine = AudioEngine::getInstance();
	_time = EngineTime::getInstance();

	ComponentsFactory::getInstance()->add("Transform", new TransformFactory());
	ComponentsFactory::getInstance()->add("ImageRenderer", new ImageRenderComponentFactory());
	ComponentsFactory::getInstance()->add("LightComponent", new LightComponentFactory());
	ComponentsFactory::getInstance()->add("RenderObject", new RenderObjectComponentFactory());
	ComponentsFactory::getInstance()->add("Listener", new ListenerComponentFactory());
	ComponentsFactory::getInstance()->add("AudioSource", new AudioSourceComponentFactory());
	ComponentsFactory::getInstance()->add("RigidBody", new RigidBodyComponentFactory());
	ComponentsFactory::getInstance()->add("BoxCollider", new BoxColliderComponentFactory());
	ComponentsFactory::getInstance()->add("SphereCollider", new SphereColliderComponentFactory());
	ComponentsFactory::getInstance()->add("CapsuleCollider", new CapsuleColliderComponentFactory());
	ComponentsFactory::getInstance()->add("Camera", new CameraComponentFactory());
	ComponentsFactory::getInstance()->add("Animator", new AnimatorComponentFactory());
	ComponentsFactory::getInstance()->add("ParticleSystem", new ParticleSystemComponentFactory());
	ComponentsFactory::getInstance()->add("ButtonComponent", new ButtonComponentFactory());
	ComponentsFactory::getInstance()->add("OverlayComponent", new OverlayComponentFactory());

	_luaParser = new LuaParser();

	alredyInitialized = true;
	return true;
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
	//Eliminar escena actual
	for (auto it = _GOs.begin(); it != _GOs.end(); it) {
		if (!(*it)->getPersist()) {
			GameObject* pointer = *it;
			it = _GOs.erase(it);
			delete pointer;
			//remGameObject((*it));
		}
		else
			++it;
	}

	//Cargar escena nueva
	_luaParser->loadScene(scene);
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
	int calls = _time->fixedUpdateRequired();

	if (calls == 0) return;

	for (calls; calls > 0; --calls) {
		for (auto& it : _GOs) {
			it->fixedUpdate();
		}
	}
	_time->fixedTimeUpdate();
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
	for (auto go : _GOs) {
		delete go; go = nullptr;
	}

	if (_graphicsEngine != nullptr) {
		_graphicsEngine->shutdown();
	}
	if (_physxEngine != nullptr) {
		delete _physxEngine;
		_physxEngine = nullptr;
	}
	_luaParser->closeLuaVM();
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
			GameObject* pointer = *it;
			it = _GOs.erase(it);
			delete pointer;
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