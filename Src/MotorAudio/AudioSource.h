#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

class AudioSource {
public:
	AudioSource();
	~AudioSource();
	bool Play(int n);
	void Pause();
	void Stop();

	float getVolume();
	void setVolume(float v);

private:
	float _volume;
};

#endif // !AUDIOSOURCE_H