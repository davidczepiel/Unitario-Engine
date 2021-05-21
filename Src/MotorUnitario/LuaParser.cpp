#include "LuaParser.h"
#include <iostream>
#include "Vector3.h"
//#include "LuaBridge/LuaBridge.h"

#include "GameObject.h"
#include "Engine.h"
#include "Exceptions.h"
#include "Logger.h"

#include "ComponentsFactory.h"
#include "Component.h"

LuaParser::LuaParser()
{
#if (defined _DEBUG)
#pragma comment (lib, "liblua.a")
#endif
	LuaVM = luaL_newstate();
	luaL_openlibs(LuaVM);
	//TBR
	//loadScene("Assets/Levels/pruebaPhysx.lua");
}

LuaParser::~LuaParser()
{

}

bool LuaParser::loadScene(std::string scene)
{
	if (checkLua(LuaVM, luaL_dofile(LuaVM, scene.c_str()))) {
		luabridge::getGlobalNamespace(LuaVM);
		std::string baseName = "go_";
		int howManyGos = luabridge::getGlobal(LuaVM, "HowManyGameObjects");

		for (int i = 0; i < howManyGos; ++i) {

			std::string GOname = baseName + std::to_string(i);

			luabridge::LuaRef gameObject_Lua = luabridge::getGlobal(LuaVM, GOname.c_str());

			luabridge::LuaRef gameObjectData_Lua = gameObject_Lua[0];

			//Name
			std::string GO_name = gameObjectData_Lua["Name"].cast<std::string>();
			//HowMany components
			int howMany = gameObjectData_Lua["HowManyCmps"].cast<int>();
			//Persist in scene
			bool persist = gameObjectData_Lua["Persist"].cast<bool>();

			GameObject* go = Engine::getInstance()->addGameObject();
			if (persist && Engine::getInstance()->findGameObject(GO_name) != nullptr)
				continue;
			go->setName(GO_name);
			go->setPersist(persist);

			for (int x = 1; x <= howMany; x++) {
				luabridge::LuaRef componentData = gameObject_Lua[x];
				std::string type = componentData["Component"].cast <std::string>();

				//Attach component to game object
				//TODO
				try
				{
					attachComponent(go, type, componentData);
				}
				catch (const ExcepcionTAD& e)
				{
					throw LuaComponentNotFoundException("Error while inicialise component" + type + " with Lua: " + e.msg());
					Logger::getInstance()->log("Error while inicialise component with Lua: ", Logger::Level::FATAL);
				}

			}
			
		}
		Logger::getInstance()->log("Archivo de carga de escena de lua correctamente inicializado");
		return true;
	}
	Logger::getInstance()->log("Archivo de carga de escena de lua no encontrado",Logger::Level::FATAL);
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
	Component* co = ComponentsFactory::getInstance()->getComponentByName(cmp);
	co->setGameObject(go);
	co->awake(data);
	go->addComponent(co);
}

