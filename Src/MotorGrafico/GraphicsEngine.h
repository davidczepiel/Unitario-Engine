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
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GraphicsEngine* getInstance();
	void operator=(const GraphicsEngine&) = delete;
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
	/// Starts rendering
	/// </summary>
	void start();

private:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	GraphicsEngine();

	static GraphicsEngine* instance;
	Ogre::Root* root;
	Ogre::RenderWindow* window;
	SDL_Window* sdlWindow;
};
