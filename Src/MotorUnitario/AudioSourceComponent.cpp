#include "AudioSourceComponent.h"
#include "MotorAudio/AudioSource.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"
AudioSourceComponent::AudioSourceComponent(GameObject* gameObject): Component(9,gameObject), _audioSource(nullptr), _tr(nullptr), _route()
{
}

AudioSourceComponent::AudioSourceComponent(GameObject* gameObject, std::string const& route) : Component(9,gameObject), _audioSource(nullptr), _tr(nullptr), _route(route)
{
}

AudioSourceComponent::~AudioSourceComponent()
{
	delete _audioSource;
}

void AudioSourceComponent::start()
{
	_audioSource = new AudioSource();
	_tr = static_cast<Transform*>(_gameObject->getComponent(7));
}

void AudioSourceComponent::update()
{
	_audioSource->setPosition(_tr->getPosition().getX(), _tr->getPosition().getY(), _tr->getPosition().getZ());
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

void AudioSourceComponent::setAudioLoop(int id, int loop)
{
	_audioSource->setLoop(id, loop);
}

void AudioSourceComponent::setStereo(int id, bool stereo)
{
	_audioSource->set3D(id, stereo);
}

float AudioSourceComponent::getVolumeChannel() const
{
	return _audioSource->getVolumeAudio();
}

void AudioSourceComponent::setVolumeChannel(float v)
{
	_audioSource->setVolumeAudio(v);
}

void AudioSourceComponent::set3DConeSetting(float insideAngle, float outsideAngle, float outsideVolume)
{
	_audioSource->set3DConeSettings(insideAngle, outsideAngle, outsideVolume);
}

void AudioSourceComponent::set3DMinMaxDistanceChannel(float min, float max)
{
	_audioSource->set3DMinMaxDistance(min, max);
}




