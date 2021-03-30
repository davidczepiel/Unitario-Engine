#pragma once
#ifndef LISTENER_H
#define LISTENER_H

#include <fmod.hpp>

class Listener {
public:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	Listener();
	/// <summary>
	/// Destructor of the class
	/// </summary>
	~Listener();
	/// <summary>
	/// Update the position of the listener in the system of th engine
	/// </summary>
	void update();

	inline void setPosition(float x, float y, float z) { _attributes.position = { x,y,z }; }
	inline void setVecocity(float x, float y, float z) { _attributes.velocity = { x,y,z }; }
	inline void setForward(float x, float y, float z) { _attributes.forward = { x,y,z }; }
	inline void setUp(float x, float y, float z) { _attributes.up = { x,y,z }; }
	inline void setListenerNumber(int listenNumber) { _listenerNumber = listenNumber; }

private:
	//Struct with all the parametres of the listener
	FMOD_3D_ATTRIBUTES _attributes;
	//Id number of the listener
	int _listenerNumber;
};

#endif // !AUDIOENGINE_H