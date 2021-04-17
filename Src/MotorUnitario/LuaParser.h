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
#include "LuaBridge/LuaBridge.h"
class GameObject;

enum class ComponentType{ AudioSource, Transform, RigidBody, Collider, Light };

class LuaParser
{
public:
	LuaParser();
	~LuaParser();
	void test();

	/// <summary>
	/// Request the loading of a scene
	/// </summary>
	bool loadScene(std::string scene);

	/// <summary>
	/// Closes the Lua virtual machine, do this when you stop using Lua
	/// </summary>
	void closeLuaVM();

	/// <summary>
	/// Using regular Lua 
	/// </summary>
	void LuaParsingTest();

	/// <summary>
	/// Using LuaBridge Namespace library
	/// </summary>
	void luaBridgeParsingtest();
private:
	/// <summary>
	/// 
	/// </summary>
	void attachComponent(GameObject* go, std::string cmp, luabridge::LuaRef &data);

	ComponentType getComponentType(std::string cmp);

	/// <summary>
	/// Virtual Machine of Lua, all the functions related to lua will need to call this method, Luabridge or regular Lua, both
	/// </summary>
	lua_State* LuaVM;
	/// <summary>
	/// Checks if Lua found the file requested or not
	/// </summary>
	/// <param name="L">Lua virtual machine</param>
	/// <param name="r">A lua command, such as luaL_dofile()</param>
	/// <returns>returns true if the file was found</returns>
	bool checkLua(lua_State* L, int r);
};

#endif LUAPARSER_H