#include "..\..\Src\MotorAudio\AudioSource.h"

AudioSource::AudioSource()
{
}

AudioSource::~AudioSource()
{
}

bool AudioSource::Play(int n)
{
	return false;
}

void AudioSource::Pause()
{
}

void AudioSource::Stop()
{
}

float AudioSource::getVolume()
{
	return _volume;
}

void AudioSource::setVolume(float v)
{
	_volume = v;
}
