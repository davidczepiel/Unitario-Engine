#include "LuaParser.h"
#include <iostream>
#include "Vector3.h"
//#include "LuaBridge/LuaBridge.h"

#include "GameObject.h"
#include "AudioSourceComponent.h"
#include "Transform.h"

LuaParser::LuaParser()
{
#if (defined _DEBUG)
#pragma comment (lib, "liblua.a")
#endif
	LuaVM = luaL_newstate();
	luaL_openlibs(LuaVM);
	loadScene("Assets/Levels/prueba.lua");
}

LuaParser::~LuaParser()
{

}



bool LuaParser::loadScene(std::string scene)
{
	if (checkLua(LuaVM, luaL_dofile(LuaVM, scene.c_str()))) {
		luabridge::getGlobalNamespace(LuaVM);
		std::string baseName = "go_";
		for (int i = 0; i < 2; ++i) {

			std::string GOname = baseName + std::to_string(i);

			luabridge::LuaRef gameObject_Lua = luabridge::getGlobal(LuaVM, GOname.c_str());

			luabridge::LuaRef gameObjectData_Lua = gameObject_Lua[0];

			//Name
			std::string GO_name = gameObjectData_Lua["Name"].cast<std::string>();
			//HowMany components
			int howMany = gameObjectData_Lua["HowMany"].cast<int>();

			GameObject* go = new GameObject();

			for (int x = 1; x <= howMany; x++) {
				luabridge::LuaRef componentData = gameObject_Lua[x];
				std::string type = componentData["Component"].cast <std::string>();

				//Attach component to game object
				attachComponent(go, type, componentData);
			}
		}
		return true;
	}
	return false;
}

void LuaParser::closeLuaVM()
{
	lua_close(LuaVM);
}

bool LuaParser::checkLua(lua_State * L, int r)
{
	if (r != LUA_OK) {
		std::cout << lua_tostring(L, -1) << std::endl;
		return false;
	}
	else return true;
}


void LuaParser::attachComponent(GameObject* go, std::string cmp, luabridge::LuaRef &data) {
	switch (getComponentType(cmp)) {
		case ComponentType::AudioSource:
		{
			//Cambiar por llamada a Factoría para coger el new Y BORRAR ESTA LÍNEA
			AudioSourceComponent* as = new AudioSourceComponent(go);
			as->awake(data);
			go->addComponent(as);

			go->removeComponent(as->getId());
			break;
		}
		case ComponentType::Transform: {
			//Cambiar por llamada a Factoría para coger el new Y BORRAR ESTA LÍNEA
			Transform * tr = new Transform(go);
			tr->awake(data);
			go->addComponent(tr);

			go->removeComponent(tr->getId());
			break;
		}
	}
	
}

ComponentType LuaParser::getComponentType(std::string cmp)
{
	if(cmp == "AudioSource")
		return ComponentType::AudioSource;
	else if(cmp == "Transform")
		return ComponentType::Transform;
	else if(cmp == "RigidBody")
		return ComponentType::RigidBody;
	else if(cmp == "Collider")
		return ComponentType::Collider;

}



//void LuaParser::test()
//{
//	std::string test = "o = 4 + 5";
//
//	int r = luaL_dostring(LuaVM, test.c_str());
//	auto aux = luaL_dofile(LuaVM, "Assets/Levels/test.txt");
//	if (r == LUA_OK) {
//		lua_getglobal(LuaVM, "o");
//		if (lua_isnumber(LuaVM, -1)) {
//			int a = (int)lua_tonumber(LuaVM, -1);
//			std::cout << "suma guay " << a << std::endl;
//		}
//	}
//	else
//	{
//		std::cout << lua_tostring(LuaVM, -1) << std::endl;
//	}
//
//	if (aux == LUA_OK) {
//		int b = (int)lua_tonumber(LuaVM, -1);
//		std::cout << "archivo guay " << b << std::endl;
//	}
//	else std::cout << "error archivo" << std::endl;
//
//}

//void LuaParser::LuaParsingTest()
//{
//	struct auxiliar
//	{
//		Vector3 transform;
//		std::string name;
//		int level;
//	} algo;
//
//	if (checkLua(LuaVM, luaL_dofile(LuaVM, "Assets/Levels/prueba.lua"))) {
//		//Se consiguen las variables en el .lua pusheando y moviendo la stack
//		lua_getglobal(LuaVM, "player");
//		if (lua_istable(LuaVM, -1)) {
//			lua_pushstring(LuaVM, "Name");
//			lua_gettable(LuaVM, -2);
//			algo.name = lua_tostring(LuaVM, -1);
//			lua_pop(LuaVM, 1);
//
//			lua_pushstring(LuaVM, "X");
//			lua_gettable(LuaVM, -2);
//			algo.transform.setX(lua_tonumber(LuaVM, -1));
//			lua_pop(LuaVM, 1);
//
//			lua_pushstring(LuaVM, "Y");
//			lua_gettable(LuaVM, -2);
//			algo.transform.setY(lua_tonumber(LuaVM, -1));
//			lua_pop(LuaVM, 1);
//
//
//			lua_pushstring(LuaVM, "Level");
//			lua_gettable(LuaVM, -2);
//			algo.level = lua_tonumber(LuaVM, -1);
//			lua_pop(LuaVM, 1);
//		}
//	}
//	std::cout << "Player: " << algo.name << " con Coordenadas: " << algo.transform.getX() << "," << algo.transform.getY() << " Nivel: " << algo.level << std::endl;
//
//	//lua_getglobal(LuaVM, "player");
//	//auto a = luaL_dofile(LuaVM, "json2lua.lua");
//	//lua_getglobal(LuaVM, "fruit");
//}
//void printDone(const std::string& s) {
//	std::cout << s << std::endl;
//}
//void LuaParser::luaBridgeParsingtest()
//{
//	luabridge::getGlobalNamespace(LuaVM);
//	luabridge::LuaRef pruebaLua = luabridge::getGlobal(LuaVM, "player");
//
//	std::string nombre = pruebaLua["Name"].cast<std::string>();
//
//	int Id = pruebaLua["Id"].cast<int>();
//
//	luabridge::LuaRef Level = pruebaLua["Level"];
//	std::string Nivel = Level.cast<std::string>();
//
//	//std::string transform = Transform.cast<std::string>();
//	if (!pruebaLua.isNil()) {
//		luabridge::LuaRef transform = pruebaLua["Transform"];
//		Vector3 aux = { transform["X"].cast<double>(),transform["Y"].cast<double>(),transform["Z"].cast<double>() };
//	}
//
//
//	lua_getglobal(LuaVM, "getObjetos");
//	if (lua_isfunction(LuaVM, -1)) {
//		//lua_pushnumber(LuaVM, 0);
//		luabridge::getGlobalNamespace(LuaVM).
//			addFunction("printDone", printDone);
//		luabridge::LuaRef getObjetos = luabridge::getGlobal(LuaVM, "getObjetos");
//
//		luabridge::LuaRef objeto = getObjetos(0);
//		std::string ObjetoName = objeto["Name"].cast<std::string>();
//		int ObjetoId = objeto["Id"].cast<int>();
//		std::cout << "objeto: " << ObjetoName << " con id: " << ObjetoId << std::endl;
//	}
//}