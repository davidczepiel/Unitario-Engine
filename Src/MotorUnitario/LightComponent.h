#pragma once
#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "Component.h"
#include "Colour.h"

class Transform;
class GameObject;
class Light;

class LightComponent : public Component
{
public:
	enum class LightType {
		/// Point light sources give off light equally in all directions, so require only position not direction
		POINT = 0,
		/// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
		DIRECTIONAL = 1,
		/// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
		SPOTLIGHT = 2
	};

public:

	LightComponent();

	~LightComponent();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Initialize the component
	/// </summary>
	virtual void start() override;

	/// <summary>
	/// Updates Light position
	/// </summary>
	void update() override;

	/// <summary>
	/// Changes light type to given type
	/// </summary>
	/// <param name="type">: light's type</param>
	void setType(LightComponent::LightType type);

	/// <summary>
	/// Return light's type
	/// </summary>
	/// <returns>Light's type</returns>
	LightComponent::LightType getLightType();

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="red">: R parameter of the color</param>
	/// <param name="green">: G parameter of the color</param>
	/// <param name="blue">: B parameter of the color</param>
	void setDiffuse(float red, float green, float blue);

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="diffuse">: Colour structure</param>
	void setDiffuse(const Colour& diffuse);

	/// <summary>
	/// Returns light's diffuse color
	/// </summary>
	/// <returns>diffuse colour</returns>
	const Colour& getDiffuse() const;

	/// <summary>
	/// Sets light's specular to given color
	/// </summary>
	/// <param name="red">: R parameter of the color</param>
	/// <param name="green">: G parameter of the color</param>
	/// <param name="blue">: B parameter of the color</param>
	void setSpecular(float red, float green, float blue);

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="specular">: Colour structure</param>
	void setSpecular(const Colour& specular);

	/// <summary>
	/// Returns light's specular color
	/// </summary>
	/// <returns>specular colour</returns>
	const Colour& getSpecular() const;

	/// <summary>
	/// Sets attenuation for the light
	/// </summary>
	/// <param name="range">: The absolute upper range of the light in world units.</param>
	/// <param name="constant">: The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation.</param>
	/// <param name="linear">: The linear factor in the attenuation formula: 1 means attenuate evenly over the distance.</param>
	/// <param name="quadratic">: The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.</param>
	void setAttenuation(float range, float constant, float linear, float quadratic);

	/// <summary>
	/// Returns light's attenuation range
	/// </summary>
	/// <returns>The absolute upper range of the light in world units</returns>
	const float getAttenuationRange() const;

	/// <summary>
	/// Returns the constant factor in the attenuation formula
	/// </summary>
	/// <returns>Constant factor of light's attenuation</returns>
	const float getAttenuationConstant() const;

	/// <summary>
	/// Returns the linear factor in the attenuation formula
	/// </summary>
	/// <returns>Linear factor of light's attenuation</returns>
	const float getAttenuationLinear() const;

	/// <summary>
	/// Returns the quadric factor in the attenuation formula
	/// </summary>
	/// <returns>quadric factor of light's attenuation</returns>
	const float getAttenuationQuadric() const;

	/// <summary>
	/// Only usefull if the type of this light is set to SpotLight
	/// </summary>
	/// <param name="innerAngle">: Angle covered by the bright inner cone.</param>
	/// <param name="outerAngle">: Angle covered by the outer cone.</param>
	/// <param name="fallof">:  The rate of falloff between the inner and outer cones. 1.0 means a linear falloff,
	///							less means slower falloff, higher means faster falloff.</param>
	void setSpotlightRange(float innerAngle, float outerAngle, float falloff);

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight fallOf</returns>
	const float getSpotlightFallOff() const;

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight inner angle</returns>
	const float getSpotlightInnerAngle() const;

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight outter angle</returns>
	const float getSpotlightOuterAngle() const;

	/// <summary>
	/// Sets the intensity of this light
	/// </summary>
	/// <param name="power">: Default value is already set at 1</param>
	void setPowerScale(float power);

	/// <summary>
	/// Return the intensity of this light
	/// </summary>
	/// <returns>intensity of this light</returns>
	const float getPowerScale() const;

	/// <summary>
	/// Changes light visibility
	/// </summary>
	/// <param name="visible">true means visible</param>
	void setVisible(bool visible);

	/// <summary>
	/// Returns the value set by MovableObject::setVisible only.
	/// </summary>
	/// <returns>if it's visible or not</returns>
	const bool getVisible() const;

	/// <summary>
	///	String to light type converter required for lua.
	/// </summary>
	/// <returns>if it's visible or not</returns>
	const LightComponent::LightType convertLightType(std::string type);


private:

	/// <summary>
	/// Redefined by child classes called when component is enabled
	/// </summary>
	void onEnable() override;

	/// <summary>
	/// Redefined by child classes called when component is disabled
	/// </summary>
	void onDisable() override;

	Light* _light;

	Transform* _tr;
};

#endif LIGHT_COMPONENT_H
