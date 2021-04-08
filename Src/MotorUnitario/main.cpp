#define SDL_MAIN_HANDLED

#include "Engine.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	Engine* prueba = Engine::getInstance();
	prueba->init();
	prueba->run();

	return 0;
}