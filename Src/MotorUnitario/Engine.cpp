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

#include "Factories.h"

std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() : _physxEngine(nullptr),  _graphicsEngine(nullptr), _audioEngine(nullptr),
	_GOs(), _deleteGOs(), 
	_inputManager(nullptr), _time(nullptr), _luaParser(nullptr),
	_run(true), alredyInitialized(false), _changeScene(false), scenesPath(""), _currentScene("")
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

	cleanUpGameObjects();
	if (_changeScene)
		changeScene();
}

bool Engine::init(std::string const& resourcesPath, std::string const& scenesP)
{
	if (alredyInitialized) {
		Logger::getInstance()->log("Engine class is already initialized", Logger::Level::WARN);
		return false;
	}

	scenesPath = scenesP + '/';

	//-------------InputManager--------------
	_inputManager = InputManager::getInstance();
	//--------------GraphicsEngine---------------------
	GraphicsEngine::CreateInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	_graphicsEngine->setResourcePath(resourcesPath);
	if (!_graphicsEngine->initializeRenderEngine()) {
		Logger::getInstance()->log("Graphics Engine init error", Logger::Level::ERROR);
		throw "Graphics Engine init error";
	}
	//--------------PhysXEngine--------------------
	PhysxEngine::CreateInstance();
	_physxEngine = PhysxEngine::getPxInstance();
	_physxEngine->init();
	//---------------AudioEngine--------------------
	AudioEngine::CreateInstance();
	_audioEngine = AudioEngine::getInstance();

	_time = EngineTime::getInstance();

	initEngineFactories();

	_luaParser = new LuaParser();

	alredyInitialized = true;
	return true;
}

void Engine::run()
{
	while (_run)
	{
		tick();
	}

	shutDown();
}

void Engine::changeScene(const std::string& scene)
{
	_currentScene = scene;
	_changeScene = true;
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

void Engine::initEngineFactories()
{
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
}

void Engine::cleanUpGameObjects()
{
	for (GameObject* go : _deleteGOs) {
		_GOs.remove(go);
		delete go; go = nullptr;
	}
	_deleteGOs.clear();
}

void Engine::changeScene()
{
	_changeScene = false;
	//Remove current scene
	for (auto it = _GOs.begin(); it != _GOs.end();) {
		if (!(*it)->getPersist()) {
			GameObject* go = *it;
			it = _GOs.erase(it);
			delete go;
		}
		else
			++it;
	}

	//Load new scene
	_luaParser->loadScene(scenesPath + _currentScene);

	start();
}

GameObject* Engine::addGameObject()
{
	_GOs.push_back(new GameObject());
	return _GOs.back();
}

void Engine::remGameObject(GameObject* GO)
{
	_deleteGOs.push_back(GO);
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