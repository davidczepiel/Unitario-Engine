#include "LightComponent.h"
#include "ComponentIDs.h"
#include "GameObject.h"
#include "includeLUA.h"

LightComponent::LightComponent() :Component(ComponentId::LightComponent), _light(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _light; _light = nullptr;
}

void LightComponent::awake(luabridge::LuaRef& data)
{
	_light = new Light(_gameObject->getName());

	if (LUAFIELDEXIST(Direction))
		_light->setDirection(data["Direction"]["X"].cast<float>(), data["Direction"]["Y"].cast<float>(), data["Direction"]["Z"].cast<float>());

	if (LUAFIELDEXIST(LightType))
		_light->setLightType(convertLightType(data["LightType"]));

	if (LUAFIELDEXIST(Visible))
		_light->setVisible(GETLUAFIELD(Visible, bool));

	if (LUAFIELDEXIST(Diffuse))
		_light->setDiffuse(data["Diffuse"]["Red"].cast<float>(), data["Diffuse"]["Green"].cast<float>(), data["Diffuse"]["Blue"].cast<float>());

	if (LUAFIELDEXIST(Specular))
		_light->setSpecular(data["Specular"]["Red"].cast<float>(), data["Specular"]["Green"].cast<float>(), data["Specular"]["Blue"].cast<float>());

	if (LUAFIELDEXIST(Attenuation))
		_light->setAttenuation(data["Attenuation"]["Range"].cast<float>(), data["Attenuation"]["Constant"].cast<float>(),
			data["Attenuation"]["Linear"].cast<float>(), data["Attenuation"]["Quadratic"].cast<float>());

	if (LUAFIELDEXIST(SpotLightRange))
		_light->setSpotlightRange(data["SpotLightRange"]["InnerAngle"].cast<float>(), data["SpotLightRange"]["OuterAngle"].cast<float>(),
			data["SpotLightRange"]["FallOf"].cast<float>());

}

const Light::LightType LightComponent::convertLightType(std::string type)
{
	if (type == "POINT") return Light::LightType::POINT;
	else if (type == "DIRECTIONAL") return Light::LightType::DIRECTIONAL;
	else if (type == "SPOTLIGHT") return Light::LightType::SPOTLIGHT;
	//else throw UknownLightTypeException
}

void LightComponent::onEnable()
{
	_light->setVisible(true);
}

void LightComponent::onDisable()
{
	_light->setVisible(false);
}