#include "LightComponent.h"
#include "ComponentIDs.h"
#include "GameObject.h"
#include "includeLUA.h"
#include "Transform.h"
#include "MotorGrafico/Light.h"

LightComponent::LightComponent() :Component(ComponentId::LightComponent), _light(nullptr), _tr(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _light; _light = nullptr;
}

void LightComponent::awake(luabridge::LuaRef& data)
{
	_light = new Light(_gameObject->getName());

	if (LUAFIELDEXIST(LightType))
		_light->setLightType((Light::LightType)convertLightType(GETLUASTRINGFIELD(LightType)));
		//_light->setLightType(convertLightType(data["LightType"]));

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

	if (LUAFIELDEXIST(LightDirection))
		_light->setDirection(data["LightDirection"]["X"].cast<float>(), data["LightDirection"]["Y"].cast<float>(), data["LightDirection"]["Z"].cast<float>());

	if (LUAFIELDEXIST(Intensity))	
		_light->setPowerScale(GETLUAFIELD(Intensity, float)); 	
}

void LightComponent::start()
{
	_tr = GETCOMPONENT(Transform, ComponentId::Transform);
}

void LightComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_light->setPosition(x, y, z);
}

void LightComponent::setType(LightComponent::LightType type)
{
	_light->setLightType((Light::LightType)type);
}

LightComponent::LightType LightComponent::getLightType()
{
	return (LightComponent::LightType)_light->getLightType();
}

void LightComponent::setDiffuse(float red, float green, float blue)
{
	_light->setDiffuse(red, green, blue);
}

void LightComponent::setDiffuse(const Colour& diffuse)
{
	_light->setDiffuse(diffuse.red, diffuse.green, diffuse.blue);
}

const Colour& LightComponent::getDiffuse() const
{
	return _light->getDiffuse();
}

void LightComponent::setSpecular(float red, float green, float blue)
{
	_light->setSpecular(red, green, blue);
}

void LightComponent::setSpecular(const Colour& specular)
{
	_light->setSpecular(specular.red, specular.green, specular.blue);
}

const Colour& LightComponent::getSpecular() const
{
	return _light->getSpecular();
}

void LightComponent::setAttenuation(float range, float constant, float linear, float quadratic)
{
	_light->setAttenuation(range, constant, linear, quadratic);
}

const float LightComponent::getAttenuationRange() const
{
	return _light->getAttenuationRange();
}

const float LightComponent::getAttenuationConstant() const
{
	return _light->getAttenuationConstant();
}

const float LightComponent::getAttenuationLinear() const
{
	return _light->getAttenuationLinear();
}

const float LightComponent::getAttenuationQuadric() const
{
	return _light->getAttenuationQuadric();
}

void LightComponent::setSpotlightRange(float innerAngle, float outerAngle, float falloff)
{
	_light->setSpotlightRange(innerAngle, outerAngle, falloff);
}

const float LightComponent::getSpotlightFallOff() const
{
	return _light->getSpotlightFallOff();
}

const float LightComponent::getSpotlightInnerAngle() const
{
	return _light->getSpotlightInnerAngle();
}

const float LightComponent::getSpotlightOuterAngle() const
{
	return _light->getSpotlightOuterAngle();
}

void LightComponent::setPowerScale(float power)
{
	_light->setPowerScale(power);
}

const float LightComponent::getPowerScale() const
{
	return _light->getPowerScale();
}

void LightComponent::setVisible(bool visible)
{
	_light->setVisible(visible);
}

const bool LightComponent::getVisible() const
{
	return _light->getVisible();
}

const LightComponent::LightType LightComponent::convertLightType(std::string type)
{
	if (type == "POINT") return LightComponent::LightType::POINT;
	else if (type == "DIRECTIONAL") return LightComponent::LightType::DIRECTIONAL;
	else if (type == "SPOTLIGHT") return LightComponent::LightType::SPOTLIGHT;
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