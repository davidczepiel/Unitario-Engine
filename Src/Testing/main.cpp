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
		LuaParser* l = new LuaParser();
		Engine* prueba = Engine::getInstance();

		prueba->init();
		prueba->run();
	}
	catch (const ExcepcionTAD& e) {
		Logger::getInstance()->log(e.msg(), Logger::Level::FATAL);
	}

	return 0;
}
