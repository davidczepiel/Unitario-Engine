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

	~ParticleSystemComponent();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;
	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start() override;
	/// <summary>
	/// Update the component
	/// </summary>
	virtual void update() override;

	void setPath(std::string const& path);

private:
	ParticleSystem* _pSystem;
	Transform* _tr;
	// .particle route
	std::string _path;
};

ADD_COMPONENT(ParticleSystemComponent)

#endif //PARTICLESYSTEMCOMPONENT_H