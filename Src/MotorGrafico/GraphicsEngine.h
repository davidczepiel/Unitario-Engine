#pragma once

namespace Ogre {
	class Root;
	class RenderWindow;

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

private:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	GraphicsEngine();

	static GraphicsEngine* instance;
	Ogre::Root* _root;
	Ogre::RenderWindow* _window;
	Ogre::SceneManager* _sceneManager;
	SDL_Window* _sdlWindow;
};
