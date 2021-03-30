#pragma once
#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <fmod.hpp>

class AudioEngine {
public:
	~AudioEngine();

	//WIP
	/// <summary>
	/// Returns the instance of MotorUnitario, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static AudioEngine* getInstance();
	void operator=(const AudioEngine&) = delete;
	AudioEngine(AudioEngine& other) = delete;	

	void init();
	void update();
	void release();


	inline FMOD::System* getSystem() const { return _system; };
private:
	
	/// <summary>
	/// Contructor of the class
	/// </summary>
	AudioEngine();

	//COMMENTS
	static AudioEngine* _instance;

	//comments
	FMOD::System* _system;
};

#endif // !AUDIOENGINE_H