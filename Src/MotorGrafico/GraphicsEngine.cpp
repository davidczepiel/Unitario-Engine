#include "GraphicsEngine.h"
#include <OgreRoot.h>

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine() :root(nullptr), window(nullptr)
{
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	if (instance == nullptr) {
		instance = new GraphicsEngine();
	}
	return instance;
}

void GraphicsEngine::test() {
#ifdef _DEBUG
	root = new Ogre::Root("OgreDEBUG/pluginsDEBUG.cfg");
#else //RELEASE
	root = new Ogre::Root("OgreRELEASE/pluginsRELEASE.cfg");
#endif
}

void GraphicsEngine::initRoot()
{
#ifdef _DEBUG
	root = new Ogre::Root("OgreDEBUG/pluginsDEBUG.cfg");
#else //RELEASE
	root = new Ogre::Root("OgreRELEASE/pluginsRELEASE.cfg");
#endif
}

void GraphicsEngine::initWindow() {
	root->restoreConfig();
	root->initialise(false);
	Ogre::NameValuePairList params;
	Ogre::ConfigOptionMap configuracion = root->getRenderSystem()->getConfigOptions();

	window = root->createRenderWindow("Prueba", 1920, 1080, false, &params);

	root->startRendering();
}