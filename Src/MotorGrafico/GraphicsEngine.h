#pragma once
#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <string>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class FileSystemLayer;
	class SGTechniqueResolverListener;
	namespace RTShader {
		class ShaderGenerator;
	}
}
class SDL_Window;


class GraphicsEngine {
public:

	~GraphicsEngine();

	/// <summary>
	/// Returns the instance of GraphicsEngine, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GraphicsEngine* getInstance();
	GraphicsEngine& operator=(const GraphicsEngine&) = delete;
	GraphicsEngine(GraphicsEngine& other) = delete;

	/// <summary>
	/// This method initializes the Ogre Root
	/// </summary>
	void initRoot();

	/// <summary>
	/// This method loads the configuration and prepares the Ogre RenderWindow
	/// </summary>
	void initWindow();

	/// <summary>
	/// Sets up the Ogre scene
	/// </summary>
	void setup();

	/// <summary>
	/// Render one frame
	/// </summary>
	void render();

	/// <summary>
	/// Config for the window grab
	/// </summary>
	void setWindowGrab(bool _grab);

	/// <summary>
	/// Gets the Scene Manager
	/// </summary>
	inline Ogre::SceneManager* getSceneManager() { return _sceneManager; }

	inline void setResourcePath(std::string const& pathName) { _resourcesPath = pathName; }

private:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	GraphicsEngine();

	/// <summary>
	/// Locate all resources related to the path
	/// </summary>
	/// <param name="path"> Relative route to the resources.cfg</param>
	void _locateResources(std::string const& path);

	/// <summary>
	/// Load all the resources
	/// </summary>
	void _loadResources();

	//bool initialiseRTShaderSystem();

	static GraphicsEngine* instance;
	Ogre::Root* _root;
	Ogre::RenderWindow* _window;
	Ogre::SceneManager* _sceneManager;
	// File system abstraction layer
	Ogre::FileSystemLayer* _mFSLayer; 
	// The Shader generator instance.
	Ogre::RTShader::ShaderGenerator* _mShaderGenerator; 
	// Relative path to solution folder
	std::string _mSolutionPath;    
	std::string _mRTShaderLibPath;
	// Resources path relative to user
	std::string _resourcesPath;
	// Shader generator material manager listener.
	Ogre::SGTechniqueResolverListener* _mMaterialMgrListener; 
	SDL_Window* _sdlWindow;

};

#endif /*GRAPHICSENGINE.h*/