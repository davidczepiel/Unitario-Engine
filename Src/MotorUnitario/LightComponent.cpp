#include "LightComponent.h"
#include "ComponentIDs.h"
#include "GameObject.h"

LightComponent::LightComponent() :Component(ComponentId::LightComponent),_light(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _light; _light = nullptr;
}

void LightComponent::awake(luabridge::LuaRef& data)
{
	_light = new Light(_gameObject->getName());
	//_route = data["Route"].cast<std::string>();
	//std::cout << "As: " << _route << std::endl;
	//luabridge::LuaRef lua_coord = data["Coord"];
	//_position = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
	//std::cout << "Tr: X=" << _position.getX() << ", Y=" << _position.getY() << ", Z=" << _position.getZ() << std::endl;
	/*_light->setLightType(convertLightType(data["LightType"]));
	_light->setVisible(data["Visible"].cast<bool>());
	_light->setDiffuse(data["Diffuse"]["Red"].cast<float>(), data["Diffuse"]["Green"].cast<float>(), data["Diffuse"]["Blue"].cast<float>());
	_light->setSpecular(data["Specular"]["Red"].cast<float>(), data["Specular"]["Green"].cast<float>(), data["Specular"]["Blue"].cast<float>());
	_light->setAttenuation(data["Attenuation"]["Range"].cast<float>(), data["Attenuation"]["Constant"].cast<float>(), 
							data["Attenuation"]["Linear"].cast<float>(), data["Attenuation"]["Quadratic"].cast<float>());
	_light->setSpotlightRange(data["SpotLightRange"]["InnerAngle"].cast<float>(), data["SpotLightRange"]["OuterAngle"].cast<float>(), 
							data["SpotLightRange"]["FallOf"].cast<float>());*/
}

inline const Light::LightType LightComponent::convertLightType(std::string type)
{
	if (type == "POINT") return Light::LightType::POINT;
	else if (type == "DIRECTIONAL") return Light::LightType::DIRECTIONAL;
	else if (type == "SPOTLIGHT") return Light::LightType::SPOTLIGHT;
	//else throw UknownLightTypeException	
}
