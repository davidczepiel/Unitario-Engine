#include "Light.h"
#include "OgreSceneManager.h"

unsigned int Light::_lightCount = 0;

Light::Light(): _id(_lightCount++), _light(nullptr)
{
	//sceneManager debera ser un SceneManager de Ogre statico por todo el motor grafico
	//_light = sceneManager->createLight("light" + _id);

	_light->setType(Ogre::Light::LightTypes::LT_POINT);

	//TODO: Attach the light object to the sceneNode somewhere
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

void Light::setSpotlightRange(float innerAngle, float outerAngle, float fallof){
	_light->setSpotlightRange(Ogre::Radian(innerAngle), Ogre::Radian(outerAngle), fallof);
}
