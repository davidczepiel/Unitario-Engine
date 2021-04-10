#pragma once
#ifndef AUDIOSOURCECOMPONENT_H
#define AUDIOSOURCECOMPONENT_H

#include "Component.h"
#include <string>

class GameObject;
class AudioSource;

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
	void createAudio();

	/// <summary>
	/// Play the audio with the id "id"
	/// </summary>
	/// <param name="id">Id audio</param>
	void play(int id);

	/// <summary>
	/// Update the 3d position
	/// </summary>
	void update();

	/// <summary>
	/// Pause this audio sources channel
	/// </summary>
	void pause();

	/// <summary>
	/// Stop this audio sources channel
	/// </summary>
	void stop();

	/// <summary>
	/// Sets the audio loop a determined amount of times
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="loop"> loop = 0 no loop; loop = -1 normal loop; loop = n the audio will repeat n times</param>
	void setLoop(int id, int loop);

	/// <summary>
	/// Sets the option mono-stereo in the audio.
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="stereo">If true audio will be stereo. Otherwise it will be mono</param>
	void set3D(int id, bool stereo);

	/// <summary>
	/// Gets the value of the audio source volume
	/// </summary>
	float getVolumeAudio();

	/// <summary>
	/// Sets the audio volume
	/// </summary>
	void setVolumeAudio(float v);

	/// <summary>
	/// Sets the audios source directory route
	/// </summary>
	/// <param name="route">FileRoute</param>
	void setRoute(std::string const& route);

	/// <summary>
	/// Sets the anglesand attenuation levels of a 3D cone shape, for simulated occlusion which is based on direction.
	/// </summary>
	/// <param name="insideAngle">This is the angle spread within which the sound is unattenuated.</param>
	/// <param name="outsideAngle">This is the angle spread outside of which the sound is attenuated to its outsidevolume.</param>
	/// <param name="outsideVolume">Cone outside volume</param>
	void set3DConeSettings(float insideAngle, float outsideAngle, float outsideVolume);

	/// <summary>
	/// Sets the minimum and maximum audible distance for a 3D sound
	/// </summary>
	/// <param name="min">minimum distance</param>
	/// <param name="max">maximum distance</param>
	void set3DMinMaxDistance(float min, float max);

	/// <summary>
	/// Sets the current position of the entity.
	/// </summary>
	void setPosition(float x, float y, float z);

	/// <summary>
	/// Sets the current velocity of the entity.
	/// </summary>
	void setVelocity(float x, float y, float z);

private:
	AudioSource* _audioSource;
};
#endif // !AUDIOSOURCECOMPONENT_H