#include "GraphicsEngine.h"
#include <OgreRoot.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include "Exceptions.h"
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <OgreGpuProgramManager.h>

#include "OgreShaderGenerator.h"
#include <OgreMaterialManager.h>

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine() :_root(nullptr), _window(nullptr), _sceneManager(nullptr), _sdlWindow(nullptr)
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
	_mFSLayer = new Ogre::FileSystemLayer("MotorUnitario");

	std::string pluginsPath;
	pluginsPath = _mFSLayer->getConfigFilePath("plugins.cfg");

	_mSolutionPath = pluginsPath;    // IG2: añadido para definir directorios relativos al de la solución 
	_mSolutionPath.erase(_mSolutionPath.find_last_of("\\") + 1, _mSolutionPath.size() - 1);
	_mFSLayer->setHomePath(_mSolutionPath);   // IG2: para los archivos de configuración ogre. (en el bin de la solubión)
	_mSolutionPath.erase(_mSolutionPath.find_last_of("\\") + 1, _mSolutionPath.size() - 1);   // IG2: Quito /bin

#ifdef _DEBUG
	_root = new Ogre::Root("OgreDEBUG/pluginsDEBUG.cfg", "OgreDEBUG/ogreDEBUG.cfg");
#else //RELEASE
	_root = new Ogre::Root("OgreRELEASE/pluginsRELEASE.cfg", "OgreRELEASE/ogreRELEASE.cfg");
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
	if (SDL_GetWindowWMInfo(_sdlWindow, &wmInfo) == SDL_FALSE) {
		throw EGraphicEngine("Error creating window");
	}
	
	params["FSAA"] = configuracion["FSAA"].currentValue;     
	params["vsync"] = configuracion["VSync"].currentValue;
	params["gamma"] = configuracion["sRGB Gamma Conversion"].currentValue;
	params["externalWindowHandle"] = std::to_string(size_t(wmInfo.info.win.window));

	_window = _root->createRenderWindow("PruebaOgre", 1920, 1080, false, &params);

	setWindowGrab(false);
}

void GraphicsEngine::setup()
{
	_sceneManager = _root->createSceneManager();

	_locateResources("resources.cfg");
	//WIP
	//_locateResources(_resourcesPath);
	_loadResources();
}

void GraphicsEngine::_locateResources(std::string const& path) {
	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = _mFSLayer->getConfigFilePath(path);
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(_mSolutionPath + "\\media"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}

	_mRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_mRTShaderLibPath + "/HLSL", type, sec);
	}
}

//WIP
//bool GraphicsEngine::initialiseRTShaderSystem()
//{
//	if (Ogre::RTShader::ShaderGenerator::initialize())
//	{
//		_mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//		// Core shader libs not found -> shader generating will fail.
//		if (_mRTShaderLibPath.empty())
//			return false;
//		// Create and register the material manager listener if it doesn't exist yet.
//		if (!_mMaterialMgrListener) {
//			_mMaterialMgrListener = new Ogre::SGTechniqueResolverListener(_mShaderGenerator);
//			Ogre::MaterialManager::getSingleton().addListener(_mMaterialMgrListener);
//		}
//	}
//
//	return true;
//}

void GraphicsEngine::_loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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
