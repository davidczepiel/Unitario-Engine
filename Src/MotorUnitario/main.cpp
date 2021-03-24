#include "MotorGrafico/main.h"
#include "MotorAudio/main.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	test();
	saluda();

	return 0;
}