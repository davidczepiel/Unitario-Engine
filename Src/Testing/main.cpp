#include "MotorUnitario/Engine.h"
#include "MotorUnitario/Exceptions.h"
#include "MotorUnitario/Logger.h"
#include "MotorUnitario/LuaParser.h"
#include "MotorUnitario/Transform.h"
#include "MotorUnitario/RigidBodyComponent.h"
#include "MotorUnitario/GameObject.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	try {
		LuaParser* l = new LuaParser();
		Engine* prueba = Engine::getInstance();

		prueba->init();
		GameObject* go = prueba->addGameObject();

		Transform* tr = new Transform();
		go->addComponent(tr);

		RigidBodyComponent* rb = new RigidBodyComponent(go, RigidBodyComponent::Type::Box);
		go->addComponent(rb);
		prueba->run();
	}
	catch (const ExcepcionTAD& e) {
		Logger::getInstance()->log(e.msg(), Logger::Level::FATAL);
	}

	return 0;
}
