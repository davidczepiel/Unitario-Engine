#include "MotorGrafico/main.h"
#include "MotorAudio/main.h"
#include "MotorFisico/main.h"

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

	return 0;
}


