#include "MotorUnitario.h"
//WIP
#include "MotorGrafico/main.h"
#include "MotorUnitario/GameObject.h"

MotorUnitario::MotorUnitario() : _run(true)
{
}

MotorUnitario::~MotorUnitario()
{
}

MotorUnitario* MotorUnitario::getInstance()
{
	if (instance == nullptr) {
		instance = new MotorUnitario();
	}
	return instance;
}

void MotorUnitario::Tick()
{
	Update();
	//WIP
	FixedUpdate();
	LateUpdate();
}

void MotorUnitario::Init()
{
	//Llama al de ogre, temporal
	test();
}

void MotorUnitario::Run()
{
	while (_run)
	{
		Tick();

	}
}

void MotorUnitario::ChangeScene(std::string scene)
{

}

void MotorUnitario::StopExecution()
{
	_run = false;
}

void MotorUnitario::Start()
{
	for (auto& it : GOs) {
		it->start();
	}
}

void MotorUnitario::FixedUpdate()
{
	for (auto& it : GOs) {
		it->fixedUpdate();
	}
}

void MotorUnitario::Update()
{
	for (auto& it : GOs) {
		it->update();
	}
}

void MotorUnitario::LateUpdate()
{
	for (auto& it : GOs) {
		it->lateUpdate();
	}
}

GameObject* MotorUnitario::addGameObject()
{
	GOs.push_back(new GameObject());
	return GOs.back();
}

void MotorUnitario::remGameObject(GameObject* GO)
{
	auto it = GOs.begin();
	while (it != GOs.end()) {
		if ((*it) == GO) {
			it = GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

void MotorUnitario::remGameObjectString(std::string const& GOname)
{
	auto it = GOs.begin();
	while (it != GOs.end()) {
		if ((*it)->getName() == GOname) {
			delete (*it);
			it = GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

GameObject* MotorUnitario::findGameObject(std::string name)
{
	auto it = GOs.begin();
	while (it != GOs.end()) {
		if ((*it)->getName() == name) {
			break;
		}
		else
			it++;
	}
	return (it == GOs.end()) ? (nullptr) : (*it);
}

void MotorUnitario::FreeEnginesResources() {

}