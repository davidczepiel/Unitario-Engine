#include "GraphicsEngine.h"
#include <OgreRoot.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>


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


void GraphicsEngine::initRoot()
{
#ifdef _DEBUG
	root = new Ogre::Root("OgreDEBUG/pluginsDEBUG.cfg", "OgreDEBUG/ogreDEBUG.cfg");
#else //RELEASE
	root = new Ogre::Root("OgreRELEASE/pluginsRELEASE.cfg", "OgreRELEASE/ogreRELEASE.cfg");
#endif
}

void GraphicsEngine::initWindow() {
	root->restoreConfig();
	root->initialise(false);
	Ogre::NameValuePairList params;
	Ogre::ConfigOptionMap configuracion = root->getRenderSystem()->getConfigOptions();
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	
	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE
	std::string nombre = "Prueba";

	sdlWindow = SDL_CreateWindow(nombre.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, flags); 
	SDL_GetWindowWMInfo(sdlWindow, &wmInfo);
	
	params["FSAA"] = configuracion["FSAA"].currentValue;     
	params["vsync"] = configuracion["VSync"].currentValue;
	params["gamma"] = configuracion["sRGB Gamma Conversion"].currentValue;
	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	window = root->createRenderWindow("PruebaOgre", 1920, 1080, false, &params);
}

void GraphicsEngine::start()
{
	root->startRendering();
}
