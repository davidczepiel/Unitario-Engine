#include "MotorGrafico/main.h"
#include "MotorAudio/main.h"
#include "MotorFisico/main.h"
#include "MotorFisico/PhysxEngine.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	pruebaPx();
	test();
	saluda();
	PhysxEngine* pEngine = PhysxEngine::getPxInstance();
	pEngine->init();
	return 0;
}


