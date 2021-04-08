#pragma once
#ifndef LISTENER_H
#define LISTENER_H

namespace FMOD {
	struct FMOD_VECTOR
	{
		float x;
		float y;
		float z;
	};
	struct FMOD_3D_ATTRIBUTES
	{
		FMOD_VECTOR position;
		FMOD_VECTOR velocity;
		FMOD_VECTOR forward;
		FMOD_VECTOR up;
	};
}


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
	FMOD::FMOD_3D_ATTRIBUTES _attributes;
	//Id number of the listener
	int _listenerNumber;
};

#endif // !AUDIOENGINE_H