#define SDL_MAIN_HANDLED

#include "Engine.h"
#include <iostream>
#include "LuaParser.h"
#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	LuaParser* Lua = new LuaParser();
	Lua->test();
	Lua->closeLuaVM();

	Engine* prueba = Engine::getInstance();
	prueba->init();
	prueba->run();
	//prueba->stopExecution();

	return 0;
}