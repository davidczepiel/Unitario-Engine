#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <array>

#include "OgreLight.h"
#include "Colour.h"

class Light
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

	Light();
	~Light();

	inline void setLightType(LightType type) { _light->setType((Ogre::Light::LightTypes)type); }
	inline LightType getLightType(LightType type) { return (LightType)_light->getType(); }

	inline void setDiffuse(float red, float green, float blue) { _light->setDiffuseColour(red, green, blue); }
	inline void setDiffuse(const Colour& diffuse) { _light->setDiffuseColour(diffuse.red, diffuse.green, diffuse.blue); }
	const Colour& getDiffuse() const;

	inline void setSpecular(float red, float green, float blue) { _light->setSpecularColour(red, green, blue); }
	inline void setSpecular(const Colour& specular) { _light->setSpecularColour(specular.red, specular.green, specular.blue); }
	const Colour& getSpecular() const;

	inline void setAttenuation(float range, float constant, float linear, float quadratic) { _light->setAttenuation(range, constant, linear, quadratic); }
	inline const float getAttenuationRange() const { return _light->getAttenuationRange(); }
	inline const float getAttenuationConstant() const { return _light->getAttenuationConstant(); }
	inline const float getAttenuationLinear() const { return _light->getAttenuationLinear(); }
	inline const float getAttenuationCuadratic() const { return _light->getAttenuationQuadric(); }

	inline void setPosition(double x, double y, double z) { _light->setPosition(x, y, z); }
	const std::tuple<double, double, double>& getPosition() const;

	inline void setDirection(double x, double y, double z) { _light->setDirection(x, y, z); }
	const std::tuple<double, double, double>& getDirection();

	void setSpotlightRange(float innerAngle, float outerAngle, float fallof);
	inline const float getSpotlightFallOf() const { return _light->getSpotlightFalloff(); }
	inline const float getSpotlightInnerAngle() const { return _light->getSpotlightInnerAngle().valueRadians(); }
	inline const float getSpotlightOuterAngle() const { return _light->getSpotlightOuterAngle().valueRadians(); }

	inline void setPowerScale(float power) { _light->setPowerScale(power); }
	inline const float getPowerScale(float power) const { _light->getPowerScale(); }

	inline void setVisible(bool visible) { _light->setVisible(visible); }
	inline const bool getVisible() const { return _light->getVisible(); }

	static unsigned int _lightCount;

private:
	const unsigned int _id;
	Ogre::Light* _light;
};

#endif LIGHT_H