#pragma once
#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

namespace FMOD {
	class System;
}
class AudioEngine {
public:
	~AudioEngine();

	/// <summary>
	/// Creates the class instance
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// Returns the instance of AudioEngine, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static AudioEngine* getInstance();
	void operator=(const AudioEngine&) = delete;
	AudioEngine(AudioEngine& other) = delete;
	/// <summary>
	/// Initialize the system object and prepare FMOD for playback
	/// </summary>
	bool init();
	/// <summary>
	/// Update the system object
	/// </summary>
	void update();
	/// <summary>
	/// Closes and frees this object and its resources
	/// </summary>
	void release();

	FMOD::System* getSystem() const;

	/// <summary>
	/// Sets the global doppler scale, distance factorand log rolloff scale for all 3D sound in FMOD.
	/// </summary>
	/// <param name="dopplerScale"> General scaling factor for how much the pitch varies due to doppler shifting in 3D sound</param>
	/// <param name="distanceFactor">Relative distance factor to FMOD units. This only affects doppler</param>
	/// <param name="rolloff">Scaling factor for 3D sound rolloff or attenuation. Setting this value makes the sound drop off faster or slower.
	/// The higher the value, the faster volume will attenuate, and conversely the lower the value, the slower it will attenuate</param>
	void set_3DSettings(float dopplerScale, float distanceFactor, float rolloff);

private:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	AudioEngine();

	bool alreadyInitialized;

	static AudioEngine* _instance;
	FMOD::System* _system;
};

#endif // !AUDIOENGINE_H