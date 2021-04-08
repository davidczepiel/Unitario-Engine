#include "AudioSourceComponent.h"
#include "MotorAudio/AudioSource.h"
AudioSourceComponent::AudioSourceComponent(unsigned int id, GameObject* gameObject): Component(id,gameObject), _audioSource(nullptr)
{
}

AudioSourceComponent::AudioSourceComponent(unsigned int id, GameObject* gameObject, std::string const& route) : Component(id,gameObject), _route(route), _audioSource(nullptr)
{
}

AudioSourceComponent::~AudioSourceComponent()
{
	delete _audioSource;
}

void AudioSourceComponent::start()
{
	_audioSource = new AudioSource();
}

void AudioSourceComponent::lateUpdate()
{
	_audioSource->update();
}

void AudioSourceComponent::createAudioInChannel()
{
	_audioSource->createAudio();
}

void AudioSourceComponent::playAudio(int id)
{
	_audioSource->play(id);
}

void AudioSourceComponent::pauseChannel()
{
	_audioSource->pause();
}

void AudioSourceComponent::stopChannel()
{
	_audioSource->stop();
}



