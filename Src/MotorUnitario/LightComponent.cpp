#include "LightComponent.h"
#include "Exceptions.h"

#include <string>

unsigned int LightComponent::_lightCount = 0;

LightComponent::LightComponent() :Component(10), _id(0)
{
}

LightComponent::LightComponent(const std::string& gameObjectName, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _id(_lightCount++), _lightComponent(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _lightComponent; _lightComponent = nullptr;
}

void LightComponent::setLightType(LightType type) {
	/*_lightComponent->setLightType(type);*/
}

//LightType LightComponent::getLightType() {
//	/*return _lightComponent->getLightType(type);*/ return LightType::DIRECTIONAL;
//}

void LightComponent::setDiffuse(float red, float green, float blue) {
	/*_lightComponent->setDiffuse(red,green,blue);*/
}

// void setDiffuse(const Colour& diffuse) {/*_lightComponent->setLightType(type);*/ }

// const Colour& getDiffuse() const {/*return _lightComponent->getDiffuse();*/ }

void LightComponent::setSpecular(float red, float green, float blue) {
	/*_lightComponent->setSpecular(red,green,blue);*/
}

// void setSpecular(const Colour& specular) {/*_lightComponent->setSpecular(specular);*/ }

// const Colour& getSpecular() const {/*return _lightComponent->getSpecular();*/ }

void LightComponent::setAttenuation(float range, float constant, float linear, float quadratic) {
	/*_lightComponent->setAttenuation(range,constant,linear,quadratic);*/
}

const float LightComponent::getAttenuationRange() const {
	/*return _lightComponent->getAttenuationRange();*/  return 0;
}

const float LightComponent::getAttenuationConstant() const {
	/*return _lightComponent->getAttenuationConstant();*/ return 0;
}

const float LightComponent::getAttenuationLinear() const {
	/*return _lightComponent->getAttenuationLinear();*/ return 0;
}

const float LightComponent::getAttenuationQuadric() const {
	/*return _lightComponent->getAttenuationQuadric();*/ return 0;
}

void LightComponent::setSpotlightRange(float innerAngle, float outerAngle, float fallof) {
	/*_lightComponent->setSpotlightRange(innerAngle,outerAngle,fallof);*/
}

const float LightComponent::getSpotlightFallOff() const {
	/*return _lightComponent->getSpotlightFallOff();*/ return 0;
}

const float LightComponent::getSpotlightInnerAngle() const {
	/*return _lightComponent->getSpotlightInnerAngle();*/ return 0;
}

const float LightComponent::getSpotlightOuterAngle() const {
	/*return _lightComponent->getSpotlightOuterAngle();*/ return 0;
}

void LightComponent::setPowerScale(float power) {
	/*_lightComponent->setPowerScale(power);*/
}

const float LightComponent::getPowerScale() const {
	/*return _lightComponent->getPowerScale();*/ return 0;
}

void LightComponent::setVisible(bool visible) {
	/*_lightComponent->setVisible(visible);*/
}

const bool LightComponent::getVisible() const {
	/*return _lightComponent->getVisible();*/ return true;
}