#define SDL_MAIN_HANDLED

#include "Engine.h"
#include <iostream>
extern "C"
{
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}

#if (defined _DEBUG) || !(defined _WIN32)
#pragma comment (lib, "liblua.a")
int main() {
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	std::string test = "o = 1 + 1";
	lua_State* L =  luaL_newstate();

	int r = luaL_dostring(L, test.c_str());

	if (r == LUA_OK) {
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1)) {
			int a = (int)lua_tonumber(L, -1);
			std::cout << a << std::endl;		
			
		}
	}
	else
	{
		std::cout << lua_tostring(L, -1) << std::endl;
	}

	lua_close(L);
	Engine* prueba = Engine::getInstance();
	prueba->init();
	prueba->run();

	return 0;
}