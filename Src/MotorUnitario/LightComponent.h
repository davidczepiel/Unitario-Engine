#pragma once
#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "Component.h"
#include <string>
#include <array>
//#include "MotorGrafico/Light.h"

class LightComponent : public Component
{
public:
	enum LightType {
		/// Point light sources give off light equally in all directions, so require only position not direction
		POINT = 0,
		/// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
		DIRECTIONAL = 1,
		/// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
		SPOTLIGHT = 2
	};

public:

	LightComponent();
	LightComponent(const std::string& gameObjectName, GameObject* gameObject);
	~LightComponent();

	/// <summary>
	/// Changes light type to given type
	/// </summary>
	/// <param name="type">: light's type</param>
	inline void setLightType(LightType type) {/*_lightComponent->setLightType(type);*/ }

	/// <summary>
	/// Return light's type
	/// </summary>
	/// <returns>Light's type</returns>
	inline LightType getLightType() {/*return _lightComponent->getLightType(type);*/ return LightType::DIRECTIONAL; }

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="red">: R parameter of the color</param>
	/// <param name="green">: G parameter of the color</param>
	/// <param name="blue">: B parameter of the color</param>
	inline void setDiffuse(float red, float green, float blue) {/*_lightComponent->setDiffuse(red,green,blue);*/ }

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="diffuse">: Colour structure</param>
	//inline void setDiffuse(const Colour& diffuse) {/*_lightComponent->setLightType(type);*/ }

	/// <summary>
	/// Returns light's diffuse color
	/// </summary>
	/// <returns>diffuse colour</returns>
	//inline const Colour& getDiffuse() const {/*return _lightComponent->getDiffuse();*/ }

	/// <summary>
	/// Sets light's specular to given color
	/// </summary>
	/// <param name="red">: R parameter of the color</param>
	/// <param name="green">: G parameter of the color</param>
	/// <param name="blue">: B parameter of the color</param>
	inline void setSpecular(float red, float green, float blue) {/*_lightComponent->setSpecular(red,green,blue);*/ }

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="specular">: Colour structure</param>
	//inline void setSpecular(const Colour& specular) {/*_lightComponent->setSpecular(specular);*/ }

	/// <summary>
	/// Returns light's specular color
	/// </summary>
	/// <returns>specular colour</returns>
	//inline const Colour& getSpecular() const {/*return _lightComponent->getSpecular();*/ }

	/// <summary>
	/// Sets attenuation for the light
	/// </summary>
	/// <param name="range">: The absolute upper range of the light in world units.</param>
	/// <param name="constant">: The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation.</param>
	/// <param name="linear">: The linear factor in the attenuation formula: 1 means attenuate evenly over the distance.</param>
	/// <param name="quadratic">: The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.</param>
	inline void setAttenuation(float range, float constant, float linear, float quadratic) {/*_lightComponent->setAttenuation(range,constant,linear,quadratic);*/ }

	/// <summary>
	/// Returns light's attenuation range
	/// </summary>
	/// <returns>The absolute upper range of the light in world units</returns>
	inline const float getAttenuationRange() const {/*return _lightComponent->getAttenuationRange();*/  return 0; }

	/// <summary>
	/// Returns the constant factor in the attenuation formula
	/// </summary>
	/// <returns>Constant factor of light's attenuation</returns>
	inline const float getAttenuationConstant() const {/*return _lightComponent->getAttenuationConstant();*/ return 0; }

	/// <summary>
	/// Returns the linear factor in the attenuation formula
	/// </summary>
	/// <returns>Linear factor of light's attenuation</returns>
	inline const float getAttenuationLinear() const {/*return _lightComponent->getAttenuationLinear();*/ return 0; }

	/// <summary>
	/// Returns the quadric factor in the attenuation formula
	/// </summary>
	/// <returns>quadric factor of light's attenuation</returns>
	inline const float getAttenuationQuadric() const {/*return _lightComponent->getAttenuationQuadric();*/ return 0; }

	/// <summary>
	/// Only usefull if the type of this light is set to SpotLight
	/// </summary>
	/// <param name="innerAngle">: Angle covered by the bright inner cone.</param>
	/// <param name="outerAngle">: Angle covered by the outer cone.</param>
	/// <param name="fallof">:  The rate of falloff between the inner and outer cones. 1.0 means a linear falloff,
	///							less means slower falloff, higher means faster falloff.</param>
	inline void setSpotlightRange(float innerAngle, float outerAngle, float fallof) {/*_lightComponent->setSpotlightRange(innerAngle,outerAngle,fallof);*/ }

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight fallOf</returns>
	inline const float getSpotlightFallOff() const {/*return _lightComponent->getSpotlightFallOff();*/ return 0; }

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight inner angle</returns>
	inline const float getSpotlightInnerAngle() const {/*return _lightComponent->getSpotlightInnerAngle();*/ return 0; }

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight outter angle</returns>
	inline const float getSpotlightOuterAngle() const {/*return _lightComponent->getSpotlightOuterAngle();*/ return 0; }

	/// <summary>
	/// Sets the intensity of this light
	/// </summary>
	/// <param name="power">: Default value is already set at 1</param>
	inline void setPowerScale(float power) {/*_lightComponent->setPowerScale(power);*/ }

	/// <summary>
	/// Return the intensity of this light
	/// </summary>
	/// <returns>intensity of this light</returns>
	inline const float getPowerScale() const {/*return _lightComponent->getPowerScale();*/ return 0; }

	/// <summary>
	/// Changes light visibility
	/// </summary>
	/// <param name="visible">true means visible</param>
	inline void setVisible(bool visible) {/*_lightComponent->setVisible(visible);*/ }

	/// <summary>
	/// Returns the value set by MovableObject::setVisible only.
	/// </summary>
	/// <returns>if it's visible or not</returns>
	inline const bool getVisible() const {/*return _lightComponent->getVisible();*/ return true; }

	/// <summary>
	/// Static count of lights, used so each Light has a unique name
	/// </summary>
	static unsigned int _lightCount;

private:
	const unsigned int _id;
	Component* _lightComponent;
};

#endif LIGHTCOMPONENT_H