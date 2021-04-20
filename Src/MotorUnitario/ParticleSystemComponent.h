#pragma once
#ifndef PARTICLESYSTEMCOMPONENT_H
#define PARTICLESYSTEMCOMPONENT_H

#include "Component.h"
#include <string>

class ParticleSystem;
class Transform;

class ParticleSystemComponent: public Component
{
public:
	/// <summary>
	/// Default constructor of the class
	/// </summary>
	ParticleSystemComponent();
	ParticleSystemComponent(GameObject* gameObject);
	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="path">: path of the file</param>
	ParticleSystemComponent(GameObject* gameObject, std::string const& path);
	/// <summary>
	/// Destructor of the class 
	/// </summary>
	~ParticleSystemComponent();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;
	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start();
	/// <summary>
	/// Update the component
	/// </summary>
	virtual void update();

	void setPath(std::string const& path);

private:
	ParticleSystem* _pSystem;
	Transform* _tr;
	// .particle route
	std::string _path;
};

#endif AUDIOSOURCECOMPONENT_H