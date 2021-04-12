#pragma once
#ifndef LUAPARSER_H
#define LUAPARSER_H

#include <string>

/*class lualib;
class lauxlib;
class lua;*/

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class LuaParser
{
public:
	LuaParser();
	~LuaParser();
	void test();
	void closeLuaVM();
	void JsonParser();
private:
	lua_State* LuaVM;
	bool checkLua(lua_State* L, int r);
};

#endif LUAPARSER_H