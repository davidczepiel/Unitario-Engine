#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <string>
#include <vector>
#include <fmod.hpp>

class AudioSource {
public:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	AudioSource();
	AudioSource(std::string route, bool loop);
	/// <summary>
	/// Destructor of the class
	/// </summary>
	~AudioSource();

	/// <summary>
	/// Create an audio
	/// </summary>
	void createAudio();
	/// <summary>
	/// Play the audio with the id "id"
	/// </summary>
	/// <param name="id">Id audio</param>
	bool play(int id);
	/// <summary>
	/// Update the 3d position
	/// </summary>
	void update();
	/// <summary>
	/// Pause the entire channel
	/// </summary>
	void pause();
	/// <summary>
	/// Stop the entire channel
	/// </summary>
	void stop();

	/// <summary>
	/// Sets the audio loop 
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="loop"> loop = 0 no loop; loop = -1 normal loop; loop = n the audio will repeat n times</param>
	void setLoop(int id, int loop);
	/// <summary>
	/// Sets the audio loop 
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="stereo">If true audio will be stereo. Otherwise it will be mono</param>
	void set3D(int id, bool stereo);
	/// <summary>
	/// Sets the audio directory route  
	/// </summary>
	float getVolume() const;
	/// <summary>
	/// Sets the audio volume  
	/// </summary>
	inline void setVolume(float v) { _channel->setVolume(v); }
	/// <summary>
	/// Sets the audio directory route  
	/// </summary>
	/// <param name="route">FileRoute</param>
	inline void setRoute(std::string route) { _route = route; }
	/// <summary>
	/// Sets the anglesand attenuation levels of a 3D cone shape, for simulated occlusion which is based on direction.
	/// </summary>
	/// <param name="insideAngle">This is the angle spread within which the sound is unattenuated.</param>
	/// <param name="outsideAngle">This is the angle spread outside of which the sound is attenuated to its outsidevolume.</param>
	/// <param name="outsideVolume">Cone outside volume</param>
	inline void set3DConeSettings(float insideAngle, float outsideAngle, float outsideVolume) { _channel->set3DConeSettings(insideAngle, outsideAngle, outsideVolume); }
	/// <summary>
	/// Sets the minimum and maximum audible distance for a 3D sound
	/// </summary>
	/// <param name="min">minimum distance</param>
	/// <param name="max">maximum distance</param>
	inline void set3DMinMaxDistance(float min, float max) { _channel->set3DMinMaxDistance(min, max); }
	/// <summary>
	/// Sets the current position of the entity.
	/// </summary>
	inline void setPosition(float x, float y, float z) {*_position = { x,y,z }; }
	/// <summary>
	/// Sets the current velocity of the entity.
	/// </summary>
	inline void setVelocity(float x, float y, float z) { *_velocity = { x,y,z }; }
	
private:
	std::vector<FMOD::Sound*> _sound;
	//Entity position
	FMOD_VECTOR* _position;
	//Entity velocity
	FMOD_VECTOR* _velocity;
	FMOD::System* _system;
	FMOD::Channel* _channel;
	std::string _route;
};

#endif // !AUDIOSOURCE_H