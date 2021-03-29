#include "Light.h"
#include "OgreSceneManager.h"

unsigned int Light::_lightCount = 0;

Light::Light(): _id(_lightCount++), _light(nullptr)
{
	//sceneManager debera ser un SceneManager de Ogre statico por todo el motor grafico
	//_light = sceneManager->createLight("light" + _id);

	_light->setType(Ogre::Light::LightTypes::LT_POINT);
}

Light::~Light()
{
}

const Colour& Light::getDiffuse() const
{
	const Ogre::ColourValue& colourOgre = _light->getDiffuseColour();

	return Colour(colourOgre.r, colourOgre.g, colourOgre.b, colourOgre.a);
}

const Colour& Light::getSpecular() const
{
	const Ogre::ColourValue& colourOgre = _light->getSpecularColour();

	return Colour(colourOgre.r, colourOgre.g, colourOgre.b, colourOgre.a);
}

const std::tuple<double, double, double>& Light::getPosition() const
{
	const Ogre::Vector3& pos = _light->getPosition();

	return { pos.x, pos.y, pos.z };
}

const std::tuple<double, double, double>& Light::getDirection()
{
	const Ogre::Vector3& dir = _light->getDirection();

	return { dir.x, dir.y, dir.z };
}

void Light::setSpotlightRange(float innerAngle, float outerAngle, float fallof){
	_light->setSpotlightRange(Ogre::Radian(innerAngle), Ogre::Radian(outerAngle), fallof);
}
