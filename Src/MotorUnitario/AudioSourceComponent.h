#pragma once
#ifndef AUDIOSOURCECOMPONENT_H
#define AUDIOSOURCECOMPONENT_H

#include "Component.h"
#include <string>

class AudioSource;

class AudioSourceComponent: public Component
{
public:
	/// <summary>
	/// Default constructor of the class
	/// </summary>
	AudioSourceComponent(unsigned int id, GameObject* gameObject);
	/// <summary>
	/// Constructor of the class in the case we want to create a unique sound 
	/// </summary>
	/// <param name="route">c </param>
	AudioSourceComponent(unsigned int id, GameObject* gameObject, std::string const& route);
	/// <summary>
	/// Destructor of the class 
	/// </summary>
	~AudioSourceComponent();

	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start();
	/// <summary>
	/// Called each frame after update. 
	/// </summary>
	virtual void lateUpdate();
	/// <summary>
	/// Create an audio. You MUST change the route before create it.
	/// </summary>
	void createAudioInChannel();
	/// <summary>
	/// Play the audio with the id "id"
	/// </summary>
	/// <param name="id">Id audio</param>
	void playAudio(int id);
	/// <summary>
	/// Pause the entire channel
	/// </summary>
	void pauseChannel();
	/// <summary>
	/// Stop the entire channel
	/// </summary>
	void stopChannel();
	/// <summary>
	/// Sets the audio loop 
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="loop"> loop = 0 no loop; loop = -1 normal loop; loop = n the audio will repeat n times</param>
	inline void setAudioLoop(int id, int loop) { _audioSource->setLoop(id, loop); }
	/// <summary>
	/// Sets the option mono-stereo in the audio
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="stereo">If true audio will be stereo. Otherwise it will be mono</param>
	inline void setStereo(int id, bool stereo) { _audioSource->set3D(id, stereo); }
	/// <summary>
	/// Sets the audio directory route  
	/// </summary>
	inline float getVolumeChannel() const { return _audioSource->getVolume(); }
	/// <summary>
	/// Sets the audio volume  
	/// </summary>
	inline void setVolumeChannel(float v) { _audioSource->setVolume(v); }
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
	inline void set3DConeSetting(float insideAngle, float outsideAngle, float outsideVolume) { _audioSource->set3DConeSettings(insideAngle, outsideAngle, outsideVolume); }
	/// <summary>
	/// Sets the minimum and maximum audible distance for a 3D sound
	/// </summary>
	/// <param name="min">minimum distance</param>
	/// <param name="max">maximum distance</param>
	inline void set3DMinMaxDistanceChannel(float min, float max) { _audioSource->set3DMinMaxDistance(min, max); }
	/// <summary>
	/// Sets the current position of the entity.
	/// </summary>
	inline void setCurrentPosition(float x, float y, float z) { _audioSource->setPosition(x, y, z); }
	/// <summary>
	/// Sets the current velocity of the entity.
	/// </summary>
	inline void setCurrentVelocity(float x, float y, float z) { _audioSource->setVelocity(x, y, z); }

private:
	// Sound route
	std::string _route;
	AudioSource* _audioSource;
};

#endif AUDIOSOURCECOMPONENT_H