#include "GraphicsEngine.h"
#include <OgreRoot.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include "Camera.h"

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine() :_root(nullptr), _window(nullptr)
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
	_root = new Ogre::Root("OgreDEBUG/pluginsDEBUG.cfg", "OgreDEBUG/ogreDEBUG.cfg");
#else //RELEASE
	root = new Ogre::Root("OgreRELEASE/pluginsRELEASE.cfg", "OgreRELEASE/ogreRELEASE.cfg");
#endif
}

void GraphicsEngine::initWindow() {
	_root->restoreConfig();
	_root->initialise(false);
	Ogre::NameValuePairList params;
	Ogre::ConfigOptionMap configuracion = _root->getRenderSystem()->getConfigOptions();
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	
	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;
	std::string nombre = "Prueba";

	_sdlWindow = SDL_CreateWindow(nombre.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, flags);
	SDL_GetWindowWMInfo(_sdlWindow, &wmInfo);
	
	params["FSAA"] = configuracion["FSAA"].currentValue;     
	params["vsync"] = configuracion["VSync"].currentValue;
	params["gamma"] = configuracion["sRGB Gamma Conversion"].currentValue;
	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	_window = _root->createRenderWindow("PruebaOgre", 1920, 1080, false, &params);

	setWindowGrab(false);
}

void GraphicsEngine::render()
{
	_root->renderOneFrame();
}

void GraphicsEngine::setWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(_sdlWindow, grab);
	//SDL_SetRelativeMouseMode(grab);
	SDL_ShowCursor(true);
}
