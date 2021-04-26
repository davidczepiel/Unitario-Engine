#include "LuaParser.h"
#include <iostream>
#include "Vector3.h"
//#include "LuaBridge/LuaBridge.h"

#include "GameObject.h"
#include "AudioSourceComponent.h"
#include "ListenerComponent.h"
#include "Transform.h"
#include "LightComponent.h"
#include "AnimatorComponent.h"
#include "ButtonComponent.h"
#include "CameraComponent.h"
#include "ImageRenderComponent.h"
#include "OverlayComponent.h"
#include "RenderObjectComponent.h"
#include "ParticleSystemComponent.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "Engine.h"
#include "Exceptions.h"
#include "Logger.h"

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
				catch (const LuaComponentNotFoundException& e)
				{
					std::cout << e.msg() << std::endl;
					//Log?
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
	switch (getComponentType(cmp)) {
		case ComponentId::ComponentId::Transform :
		{ 
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			Transform* tr = new Transform(go);
			tr->awake(data);
			go->addComponent(tr);
			tr->setGameObject(go);
			break; 
		}
		case ComponentId::ComponentId::RenderObject: 
		{ 
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			RenderObjectComponent* r = new RenderObjectComponent();
			r->setGameObject(go);
			r->awake(data);
			go->addComponent(r);
			break; 
		}
		case ComponentId::ComponentId::ImageRender: {
			/*ImageRenderComponent* im = new ImageRenderComponent(go);
			im->awake(data);
			go->addComponent(im);*/
			break; 
		}
		case ComponentId::ComponentId::Animator: 
		{ 
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			//AnimatorComponent* a = new AnimatorComponent(go);
			//a->awake(data);
			//go->addComponent(a);
			break; 
		}
		case ComponentId::ComponentId::LightComponent: 
		{ 
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			LightComponent* l = new LightComponent();
			l->setGameObject(go);
			l->awake(data);
			go->addComponent(l);
			break; 
		}
		case ComponentId::ComponentId::ParticleSystem: 
		{ 
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			//ParticleSystemComponent* p = new ParticleSystemComponent(go);
			//p->awake(data);
			//go->addComponent(p);
			break; 
		}
		case ComponentId::ComponentId::Camera: { 
			CameraComponent* ca = new CameraComponent();
			ca->setGameObject(go);
			ca->awake(data);
			go->addComponent(ca);
			break;
		}
		case ComponentId::ComponentId::Rigidbody: { 
			RigidBodyComponent* ca = new RigidBodyComponent();
			ca->setGameObject(go);
			ca->awake(data);
			go->addComponent(ca);
			break; 
		}
		case ComponentId::ComponentId::BoxCollider: {
			BoxColliderComponent* boxColl = new BoxColliderComponent();
			boxColl->setGameObject(go);
			boxColl->awake(data);
			go->addComponent(boxColl);
			break; 
		}
		case ComponentId::ComponentId::SphereCollider: {
			SphereColliderComponent* sphColl = new SphereColliderComponent();
			sphColl->setGameObject(go);
			sphColl->awake(data);
			go->addComponent(sphColl);
			break; 
		}
		case ComponentId::ComponentId::CapsuleCollider: {
			CapsuleColliderComponent* capsColl = new CapsuleColliderComponent();
			capsColl->setGameObject(go);
			capsColl->awake(data);
			go->addComponent(capsColl);
			break;
		}
		case ComponentId::ComponentId::AudioSource: 
		{
			AudioSourceComponent* as = new AudioSourceComponent();
			as->setGameObject(go);
			as->awake(data);
			go->addComponent(as); 
			break; 
		}
		case ComponentId::ComponentId::ListenerComponent: {
			ListenerComponent* li = new ListenerComponent();
			li->setGameObject(go);
			li->awake(data);
			go->addComponent(li);
			break;
		}
		case ComponentId::ComponentId::OverlayComponent: {
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			//OverlayComponent* o = new OverlayComponent(go);
			//o->awake(data);
			//go->addComponent(o);
			break;
		}
		case ComponentId::ComponentId::ButtonComponent: {
			//Cambiar por llamada a Factor�a para coger el new Y BORRAR ESTA L�NEA
			//ButtonComponent* b = new ButtonComponent(go);
			//b->awake(data);
			//go->addComponent(b);
			break;
		}
		default:
			throw LuaComponentNotFoundException(cmp + " is not a valid name component \n");
			break;
	}	
}

unsigned int LuaParser::getComponentType(std::string cmp)
{
	if (cmp == "Transform")
		return ComponentId::ComponentId::Transform;
	else if (cmp == "ImageRender")
		return ComponentId::ComponentId::ImageRender;
	else if (cmp == "RenderObject")
		return ComponentId::ComponentId::RenderObject;
	else if(cmp == "Animator")
		return ComponentId::ComponentId::Animator;
	else if(cmp == "LightComponent")
		return ComponentId::ComponentId::LightComponent;
	else if(cmp == "ParticleSystem")
		return ComponentId::ComponentId::ParticleSystem;
	else if (cmp == "Camera")
		return ComponentId::ComponentId::Camera;
	else if (cmp == "RigidBody")
		return ComponentId::ComponentId::Rigidbody;
	else if (cmp == "BoxCollider")
		return ComponentId::ComponentId::BoxCollider;
	else if (cmp == "SphereCollider")
		return ComponentId::ComponentId::SphereCollider;
	else if (cmp == "CapsuleCollider")
		return ComponentId::ComponentId::CapsuleCollider;
	else if (cmp == "AudioSource")
		return ComponentId::ComponentId::AudioSource;
	else if (cmp == "Listener")
		return ComponentId::ComponentId::ListenerComponent;
	else if (cmp == "OverlayComponent")
		return ComponentId::ComponentId::OverlayComponent;
	else if (cmp == "ButtonComponent")
		return ComponentId::ComponentId::ButtonComponent;
}

/*		Transform = 0,
		ImageRender,
		RenderObject,
		Animator,
		LightComponent,
		ParticleSystem,
		Camera,
	
		Rigidbody,
		BoxCollider,
		SphereCollider,
		CapsuleCollider,
	
		AudioSource,
		ListenerComponent,

		OverlayComponent,
		ButtonComponent,*/

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