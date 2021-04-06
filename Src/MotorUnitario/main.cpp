#define SDL_MAIN_HANDLED

#include "Engine.h"
#include <iostream>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#if (defined _DEBUG) || !(defined _WIN32)
#pragma comment (lib, "liblua.a")
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	std::string test = "o = 4 + 5";
	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, test.c_str());
	auto aux = luaL_dofile(L, "Assets/Levels/test.lua");
	if (r == LUA_OK) {
		lua_getglobal(L, "o");
		if (lua_isnumber(L, -1)) {
			int a = (int)lua_tonumber(L, -1);
			std::cout << "suma guay " << a << std::endl;
		}
	}
	else
	{
		std::cout << lua_tostring(L, -1) << std::endl;
	}

	if (aux == LUA_OK) {
		int b = (int)lua_tonumber(L, -1);
		std::cout << "archivo guay " << b << std::endl;
	}
	else std::cout << "error archivo" << std::endl;

	lua_close(L);
	Engine* prueba = Engine::getInstance();
	prueba->init();
	prueba->run();
	//prueba->stopExecution();

	return 0;
}