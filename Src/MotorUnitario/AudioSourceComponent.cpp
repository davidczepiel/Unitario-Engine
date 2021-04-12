#include "AudioSourceComponent.h"
#include "MotorAudio/AudioSource.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"
#include "ComponentIDs.h"

AudioSourceComponent::AudioSourceComponent(GameObject* gameObject): Component(ComponentId::AudioSource, gameObject), _audioSource(nullptr), _tr(nullptr), _route()
{
}

AudioSourceComponent::AudioSourceComponent() : Component(8),_audioSource(nullptr)
{
}

AudioSourceComponent::AudioSourceComponent(std::string const& route, GameObject* gameObject) :Component(/*ComponentId::ImageRender*/1, gameObject), _audioSource(nullptr)
{
	_audioSource = new AudioSource(route);
}

AudioSourceComponent::AudioSourceComponent(GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _audioSource(nullptr)
{
	_audioSource = new AudioSource();
}

AudioSourceComponent::~AudioSourceComponent()
{
	delete _audioSource; _audioSource == nullptr;
}

void AudioSourceComponent::createAudio()
{
	_audioSource->createAudio();
}

void AudioSourceComponent::play(int id)
{
	_audioSource->play(id);
}

void AudioSourceComponent::update()
{
	_audioSource->update();
}

void AudioSourceComponent::pause()
{
	_audioSource->pause();
}

void AudioSourceComponent::stop() {
	_audioSource->stop();
}

void AudioSourceComponent::setLoop(int id, int loop) {
	_audioSource->setLoop(id, loop);
}

void AudioSourceComponent::set3D(int id, bool stereo) {
	_audioSource->set3D(id, stereo);
}

float AudioSourceComponent::getVolumeAudio() {
	return _audioSource->getVolumeAudio();
}

void AudioSourceComponent::setVolumeAudio(float v) {
	_audioSource->setVolumeAudio(v);
}

inline void AudioSourceComponent::setRoute(std::string const& route) {
	_audioSource->setRoute(route);
}

void AudioSourceComponent::set3DConeSettings(float insideAngle, float outsideAngle, float outsideVolume) {
	_audioSource->set3DConeSettings(insideAngle, outsideAngle, outsideVolume);
}

void AudioSourceComponent::set3DMinMaxDistance(float min, float max) {
	_audioSource->set3DMinMaxDistance(min, max);
}

void AudioSourceComponent::setPosition(float x, float y, float z) {
	_audioSource->setPosition(x, y, z);
}

void AudioSourceComponent::setVelocity(float x, float y, float z) {
	_audioSource->setVelocity(x, y, z);
}