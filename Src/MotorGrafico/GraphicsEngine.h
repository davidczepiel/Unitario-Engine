#pragma once
#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <string>
#include <memory>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class FileSystemLayer;
	class Viewport;
	class Camera;

	class OverlaySystem;
	class OverlayManager;
	namespace RTShader {
		class ShaderGenerator;
	}
}

class RTSSDefaultTechniqueListener;
class SDL_Window;

class GraphicsEngine {
public:

	~GraphicsEngine();

	/// <summary>
	/// Returns the instance of GraphicsEngine, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GraphicsEngine* getInstance();

	/// <summary>
	/// Creates the class instance
	/// </summary>
	static void CreateInstance();

	GraphicsEngine& operator=(const GraphicsEngine&) = delete;
	GraphicsEngine(GraphicsEngine& other) = delete;

	/// <summary>
	/// Initializes the root, window and set ups the scene
	/// </summary>
	bool initializeRenderEngine();

	/// <summary>
	/// Free all resources in this engine
	/// </summary>
	void shutdown();

	/// <summary>
	/// Restores default scheme, unregisters the technique manager listener and destroy RTSS
	/// </summary>
	void destroyRTShaderSystem();

	/// <summary>
	/// Render one frame
	/// </summary>
	void render();

	/// <summary>
	/// Config for the window grab
	/// </summary>
	/// <param name="_grab"> bool that determines the window grab mode</param>
	void setWindowGrab(bool _grab);

	/// <summary>
	/// Sets the .cfg game file path
	/// </summary>
	/// <param name="pathName"></param>
	inline void setResourcePath(std::string const& pathName) { _resourcesPath = pathName; }

	/// <summary>
	/// Gets the Scene Manager
	/// </summary>
	inline Ogre::SceneManager* getSceneManager() { return _sceneManager; }

	/// <summary>
	/// Gets the RenderWindow
	/// </summary>
	inline Ogre::RenderWindow* getRenderWindow() { return _window; }

	/// <summary>
	/// Creates a viewport so that the camera passed can be rendered on it in a specific zOrder
	/// </summary>
	/// <param name="cam"> camera of the new viewport </param>
	/// <param name="zOrder"> zOrder of the virwport </param>
	/// <param name="x"> position X of the top left corner of the viewport</param>
	/// <param name="y"> position Y of the top left corner of the viewport</param>
	/// <param name="w"> width of the viewport</param>
	/// <param name="h"> heigh of the viewport</param>
	Ogre::Viewport* setupViewport(Ogre::Camera* cam, int zOrder, float x, float y, float w, float h);

	/// <summary>
	/// Sets the colour of the shade in the scene
	/// </summary>
	/// <param name="r"> Red color-- [0,1] </param>
	/// <param name="g"> Green color-- [0,1] </param>
	/// <param name="b"> Blue color-- [0,1] </param>
	void setShadowColour(float r, float g, float b);
	
	/// <summary>
	/// Sets the ambient light
	/// </summary>
	/// <param name="r"> Red color-- [0,1] </param>
	/// <param name="g"> Green color-- [0,1] </param>
	/// <param name="b"> Blue color-- [0,1] </param>
	void setAmbientLight(float r, float g, float b);

	/// <summary>
	/// Sets the colour viewport
	/// </summary>
	/// <param name="r"> Red color-- [0,1] </param>
	/// <param name="g"> Green color-- [0,1] </param>
	/// <param name="b"> Blue color-- [0,1] </param>
	void setViewportColour(float r, float g, float b);

	/// <summary>
	/// Disables the shadow-casts
	/// </summary>
	void disableShadows();

	/// <summary>
	/// Removes a specific vireport drom the renderWindow so that the camera attached to it doesnt get rendered anymore.
	/// </summary>
	/// <param name="vp"> Viewport that is going to be removed from the renderWindow </param>
	void removeViewport(Ogre::Viewport* vp);

	/// <summary>
	/// Puts the SDL Window in full screen or puts it back to windowed size.
	/// </summary>
	void setFullScreen();

	/// </sumary>
	/// Gets the window size
	/// </summary>
	std::pair<int, int> getWindowSize();

	/// <summary>
	/// Adds an ogre node
	/// </summary>
	/// <param name="name"> name of the new node</param>
	void addNode(const std::string& name);

	/// <summary>
	/// Removes a specific node from the scene 
	/// </summary>
	/// <param name="name"> Searches a Node given a determined name and deletes it</param>
	void removeNode(const std::string& name);

	/// <summary>
	/// Removes all nodes
	/// </summary>
	void clearScene();

private:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	GraphicsEngine();

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
	/// Locate all resources related to the path
	/// </summary>
	/// <param name="path"> Relative route to the resources.cfg</param>
	void _locateResources(std::string const& path);

	/// <summary>
	/// Load all the resources
	/// </summary>
	void _loadResources();

	/// <summary>
	/// Initialise RTSS
	/// </summary>
	bool _initialiseRTShaderSystem();

	static std::unique_ptr<GraphicsEngine> instance;
	Ogre::Root* _root;
	Ogre::RenderWindow* _window;
	// Pointer to scene Manager
	Ogre::SceneManager* _sceneManager;

	Ogre::Viewport* _defaultViewport;
	Ogre::Camera* _defaultCamera;

	// File system abstraction layer
	Ogre::FileSystemLayer* _mFSLayer;
	// The Shader generator instance.
	Ogre::RTShader::ShaderGenerator* _mShaderGenerator;
	// Ogre Listener for RTSS-Shading Generation
	RTSSDefaultTechniqueListener* _mTechniqueListener;
	// Ogre Overlay System (for GUI)
	Ogre::OverlaySystem* _overlaySystem;
	// Ogre Overlay Manager
	Ogre::OverlayManager* _oveMng;
	SDL_Window* _sdlWindow;
	// Relative path to solution folder
	std::string _mSolutionPath;
	// Resources path relative to user
	std::string _resourcesPath;
	// Windows width
	int _width;
	// Windows heigth
	int _height;

	bool alredyInitialized;
};

#endif /*GRAPHICSENGINE.h*/