#include "MotorUnitario/Engine.h"
#include "MotorUnitario/Exceptions.h"
#include "MotorUnitario/Logger.h"
#include "MotorUnitario/LuaParser.h"


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
		LuaParser l = LuaParser();
		prueba->run();
	}
	catch (const ExcepcionTAD& e) {
		Logger::getInstance()->log(e.msg(), Logger::Level::FATAL);
	}

	return 0;
}
