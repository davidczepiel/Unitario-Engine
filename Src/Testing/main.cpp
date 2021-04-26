#include "MotorUnitario/Engine.h"
#include "MotorUnitario/Exceptions.h"
#include "MotorUnitario/Logger.h"
#include "MotorUnitario/LuaParser.h"
#include "MotorUnitario/Transform.h"
#include "MotorUnitario/RigidBodyComponent.h"
#include "MotorUnitario/GameObject.h"
#include "MotorUnitario/CameraComponent.h"
#include "MotorUnitario/RenderObjectComponent.h"
#include "MotorUnitario/LightComponent.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	try {
		Engine::CreateInstance();
		Engine* prueba = Engine::getInstance();
		prueba->init("Assets/prueba.cfg");
		prueba->changeScene("Assets/Levels/pruebaPhysx.lua");
		prueba->changeScene("Assets/Levels/prueba2.lua");
		prueba->run();
	}
	catch (const ExcepcionTAD& e) {
		Logger::getInstance()->log(e.msg(), Logger::Level::FATAL);
	}

	return 0;
}
