#include "LuaParser.h"
#include <iostream>
#include "Vector3.h"
LuaParser::LuaParser()
{
#if (defined _DEBUG)
#pragma comment (lib, "liblua.a")
#endif
	LuaVM = luaL_newstate();
	luaL_openlibs(LuaVM);
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

void LuaParser::LuaParser()
{
	struct auxiliar
	{
		Vector3 transform;
		std::string name;
		int level;
	} algo;
	
	if (checkLua(LuaVM, luaL_dofile(LuaVM, "Assets/Levels/prueba.lua"))) {
		lua_getglobal(LuaVM, "player");
		if (lua_istable(LuaVM, -1)) {
			lua_pushstring(LuaVM, "Name");
			lua_gettable(LuaVM, -2);
			algo.name = lua_tostring(LuaVM, -1);
			lua_pop(LuaVM, 1);

			lua_pushstring(LuaVM, "X");
			lua_gettable(LuaVM, -2);
			algo.transform.setX(lua_tonumber(LuaVM, -1));
			lua_pop(LuaVM, 1);

			lua_pushstring(LuaVM, "Y");
			lua_gettable(LuaVM, -2);
			algo.transform.setY(lua_tonumber(LuaVM, -1));
			lua_pop(LuaVM, 1);


			lua_pushstring(LuaVM, "Level");
			lua_gettable(LuaVM, -2);
			algo.level = lua_tonumber(LuaVM, -1);
			lua_pop(LuaVM, 1);
		}
	}
	std::cout << "Player: " << algo.name << " con Coordenadas: " << algo.transform.getX() << "," << algo.transform.getY() << " Nivel: " << algo.level << std::endl;


	//auto a = luaL_dofile(LuaVM, "json2lua.lua");
	//lua_getglobal(LuaVM, "fruit");
	//std::string something = (std::string)lua_tostring(LuaVM, -1);

}

bool LuaParser::checkLua(lua_State * L, int r)
{
	if (r != LUA_OK) {
		std::cout << lua_tostring(L, -1) << std::endl;
		return false;
	}
	else return true;
}
