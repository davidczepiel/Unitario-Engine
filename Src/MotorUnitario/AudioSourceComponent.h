#pragma once
#ifndef AUDIOSOURCECOMPONENT_H
#define AUDIOSOURCECOMPONENT_H

#include "MotorAudio/AudioSource.h"
#include "Component.h"

class GameObject;

class AudioSourceComponent : public Component {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	AudioSourceComponent(std::string const& route, GameObject* gameObject);
	AudioSourceComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~AudioSourceComponent();

	/// <summary>
	/// Create an audio source
	/// </summary>
	inline void createAudio() { _audioSource->createAudio(); }

	/// <summary>
	/// Play the audio with the id "id"
	/// </summary>
	/// <param name="id">Id audio</param>
	inline void play(int id) { _audioSource->play(id); }

	/// <summary>
	/// Update the 3d position
	/// </summary>
	inline void update() { _audioSource->update(); }

	/// <summary>
	/// Pause this audio sources channel
	/// </summary>
	inline void pause() { _audioSource->pause(); }

	/// <summary>
	/// Stop this audio sources channel
	/// </summary>
	inline void stop() { _audioSource->stop(); }

	/// <summary>
	/// Sets the audio loop a determined amount of times
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="loop"> loop = 0 no loop; loop = -1 normal loop; loop = n the audio will repeat n times</param>
	inline void setLoop(int id, int loop) { _audioSource->setLoop(id, loop); }

	/// <summary>
	/// Sets the option mono-stereo in the audio.
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="stereo">If true audio will be stereo. Otherwise it will be mono</param>
	inline void set3D(int id, bool stereo) { _audioSource->set3D(id, stereo); }

	/// <summary>
	/// Gets the value of the audio source volume
	/// </summary>
	inline float getVolumeAudio() { return _audioSource->getVolumeAudio(); }

	/// <summary>
	/// Sets the audio volume
	/// </summary>
	inline void setVolumeAudio(float v) { _audioSource->setVolumeAudio(v); }

	/// <summary>
	/// Sets the audios source directory route
	/// </summary>
	/// <param name="route">FileRoute</param>
	inline void setRoute(std::string const& route) { _audioSource->setRoute(route); }

	/// <summary>
	/// Sets the anglesand attenuation levels of a 3D cone shape, for simulated occlusion which is based on direction.
	/// </summary>
	/// <param name="insideAngle">This is the angle spread within which the sound is unattenuated.</param>
	/// <param name="outsideAngle">This is the angle spread outside of which the sound is attenuated to its outsidevolume.</param>
	/// <param name="outsideVolume">Cone outside volume</param>
	inline void set3DConeSettings(float insideAngle, float outsideAngle, float outsideVolume) { _audioSource->set3DConeSettings(insideAngle, outsideAngle, outsideVolume); }

	/// <summary>
	/// Sets the minimum and maximum audible distance for a 3D sound
	/// </summary>
	/// <param name="min">minimum distance</param>
	/// <param name="max">maximum distance</param>
	inline void set3DMinMaxDistance(float min, float max) { _audioSource->set3DMinMaxDistance(min, max); }

	/// <summary>
	/// Sets the current position of the entity.
	/// </summary>
	inline void setPosition(float x, float y, float z) { _audioSource->setPosition(x, y, z); }

	/// <summary>
	/// Sets the current velocity of the entity.
	/// </summary>
	inline void setVelocity(float x, float y, float z) { _audioSource->setVelocity(x, y, z); }

private:
	AudioSource* _audioSource;
};
#endif // !AUDIOSOURCECOMPONENT_H