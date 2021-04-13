#pragma once

#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include <string>
namespace Ogre{
	class ParticleSystem;
	class SceneNode;
}
class ParticleSystem
{

public:
	/// <summary>
	/// Default constructor of the class
	/// </summary>
	ParticleSystem();
	/// <summary>
	/// Constructor of the class
	/// <param name="path">: path of the file</param>
	/// <param name="name">: name of the object</param>
	/// </summary>
	ParticleSystem(std::string const& path, std::string const& name);

	/// <summary>
	/// Destrcutor of the class
	/// </summary>
	~ParticleSystem();

	/// <summary>
	/// Initialize the particle system
	/// </summary>
	void init();
	
	void setPosition(double x, double y, double z);
	/// <summary>
	/// Sets the path where the ".particle" is it
	/// <param name="path">: path of the file</param>
	/// </summary>
	inline void setPath(std::string const& path) { _path = path; }
	/// <summary>
	/// Sets the name of the object. It's used to ogre initialization
	/// </summary>
	inline void setName(std::string const& name) { _name = name; }
private:
	// Pointer to particleSystem
	Ogre::ParticleSystem* _pSystem;
	// Pointer to sceneNode
	Ogre::SceneNode* _node;
	// path of the file
	std::string _path;
	// name of the object
	std::string _name;
};

#endif //!PARTICLESYSTEM_H