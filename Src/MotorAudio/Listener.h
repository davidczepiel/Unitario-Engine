#pragma once
#ifndef LISTENER_H
#define LISTENER_H

struct FMOD_3D_ATTRIBUTES;

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

	void setPosition(float x, float y, float z);
	void setVelocity(float x, float y, float z);
	void setForward(float x, float y, float z);
	void setUp(float x, float y, float z);
	void setListenerNumber(int listenNumber);

private:
	//Struct with all the parametres of the listener
	FMOD_3D_ATTRIBUTES* _attributes;
	//Id number of the listener
	int _listenerNumber;
};

#endif // !LISTENER_H