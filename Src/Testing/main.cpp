#include "MotorUnitario/Engine.h"
#include "MotorUnitario/Exceptions.h"
#include "MotorUnitario/Logger.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	Engine::CreateInstance();
	Engine* prueba = Engine::getInstance();
	prueba->init("Assets/prueba.cfg", "Assets/Levels");
	prueba->changeScene("pruebaPhysx.lua");
	prueba->run();

	return 0;
}