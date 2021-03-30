#include "MotorGrafico/main.h"
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

	return 0;
}


