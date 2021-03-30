#include "MotorGrafico/main.h"
#include "MotorAudio/main.h"
#include "MotorFisico/main.h"
#include <SDL.h>
#include <string>
#include "Engine.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	pruebaPx();
	Engine* prueba = Engine::getInstance();
	prueba->init();
	Sleep(1000);
	return 0;
}