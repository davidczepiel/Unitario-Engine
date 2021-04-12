#include "LuaParser.h"
#include <iostream>


LuaParser::LuaParser()
{
#if (defined _DEBUG)
#pragma comment (lib, "liblua.a")
#endif
	LuaVM = luaL_newstate();
}

LuaParser::~LuaParser()
{
}

void LuaParser::test()
{
	std::string test = "o = 4 + 5";

	int r = luaL_dostring(LuaVM, test.c_str());
	auto aux = luaL_dofile(LuaVM, "Assets/Levels/test.txt");
	if (r == LUA_OK) {
		lua_getglobal(LuaVM, "o");
		if (lua_isnumber(LuaVM, -1)) {
			int a = (int)lua_tonumber(LuaVM, -1);
			std::cout << "suma guay " << a << std::endl;
		}
	}
	else
	{
		std::cout << lua_tostring(LuaVM, -1) << std::endl;
	}

	if (aux == LUA_OK) {
		int b = (int)lua_tonumber(LuaVM, -1);
		std::cout << "archivo guay " << b << std::endl;
	}
	else std::cout << "error archivo" << std::endl;

}

void LuaParser::closeLuaVM()
{
	lua_close(LuaVM);
}

void LuaParser::JsonParser()
{

}

bool LuaParser::checkLua(lua_State * L, int r)
{
	if (r != LUA_OK) {
		std::cout << lua_tostring(L, -1) << std::endl;
		return false;
	}
	else return true;
}
