#include "AudioSourceComponent.h"
//#include "ComponentIDs.h"

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