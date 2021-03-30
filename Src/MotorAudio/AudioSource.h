#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <string>
#include <fmod.hpp>

class AudioSource {
public:
	AudioSource();
	AudioSource(std::string rute, bool loop);
	~AudioSource();

	void init();
	bool play(int n);
	void pause();
	void stop();

	inline float getVolume() const {return _volume;	}
	inline void setVolume(float v) { _volume = v; }
	inline void setRute(std::string rute) { _rute = rute; }
	
private:
	FMOD::System* _system;
	FMOD::Channel* _channel;
	FMOD::Sound* _sound;

	bool _isLoop;
	float _volume;
	std::string _rute;
};

#endif // !AUDIOSOURCE_H