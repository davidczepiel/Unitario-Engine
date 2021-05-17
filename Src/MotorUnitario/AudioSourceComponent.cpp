#include "AudioSourceComponent.h"
#include "MotorAudio/AudioSource.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"
#include "ComponentIDs.h"
#include "includeLUA.h"


AudioSourceComponent::AudioSourceComponent() : Component(ComponentId::AudioSource), _audioSource(nullptr), _tr(nullptr), _route()
{
	_audioSource = new AudioSource();
}

AudioSourceComponent::~AudioSourceComponent()
{
	delete _audioSource; _audioSource = nullptr;
}

void AudioSourceComponent::awake(luabridge::LuaRef &data)
{
	if (LUAFIELDEXIST(Route)) 
	{ 
		//en la posicion 0 no hay nada, es "Route" en si
		for (int i = 1; i <= data["Route"].length(); ++i) {
			_route.push_back(data["Route"][i].cast<std::string>());
		}
		for(int i = 0; i < _route.size(); ++i)
			std::cout << "As: " << _route[i] << std::endl;
	}
	_audioSource = new AudioSource(_route);
		if (LUAFIELDEXIST(Route)) 
	{ 
		//en la posicion 0 no hay nada, es "Route" en si
		for (int i = 1; i <= data["Route"].length(); ++i) {
			_route.push_back(data["Route"][i].cast<std::string>());
		}
		for(int i = 0; i < _route.size(); ++i)
			std::cout << "As: " << _route[i] << std::endl;
	}
	_audioSource = new AudioSource(_route);
	if (LUAFIELDEXIST(Loop)) {
		int loop = GETLUAFIELD(Loop, int);
		for (int i = 0; i < _route.size(); ++i)
			setAudioLoop(i, loop);
	}
	if (LUAFIELDEXIST(Stereo)) {
		bool stereo = GETLUAFIELD(Stereo, bool);
		for (int i = 0; i < _route.size(); ++i)
			setStereo(i, stereo);
	}
	if (LUAFIELDEXIST(Play)) {
		if (GETLUAFIELD(Play, bool)) {
			for (int i = 0; i < _route.size(); ++i){
				playAudio(i);
			}
		}
	}
	if (LUAFIELDEXIST(Volume)) {
		for (int i = 0; i < _route.size(); ++i)
			setVolumeChannel(GETLUAFIELD(Volume, float), i);
	}
	if (LUAFIELDEXIST(MinMaxDistance)) {
		for (int i = 0; i < _route.size(); ++i)
			set3DMinMaxDistanceChannel(data["MinMaxDistance"]["Min"].cast<float>(), data["MinMaxDistance"]["Min"].cast<float>(), i);
	}
}

void AudioSourceComponent::start()
{
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_audioSource->setPosition(x, y, z);
}

void AudioSourceComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_audioSource->setPosition(x, y, z);
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

void AudioSourceComponent::pauseChannel(int id)
{
	_audioSource->pause(id);
}

void AudioSourceComponent::stopChannel(int id)
{
	_audioSource->stop(id);
}

void AudioSourceComponent::setAudioLoop(int id, int loop)
{
	_audioSource->setLoop(id, loop);
}

void AudioSourceComponent::setStereo(int id, bool stereo)
{
	_audioSource->set3D(id, stereo);
}

float AudioSourceComponent::getVolumeChannel(int id) const
{
	return _audioSource->getVolumeAudio(id);
}

void AudioSourceComponent::setVolumeChannel(float v, int id)
{
	_audioSource->setVolumeAudio(v, id);
}

void AudioSourceComponent::set3DConeSetting(float insideAngle, float outsideAngle, float outsideVolume, int id)
{
	_audioSource->set3DConeSettings(insideAngle, outsideAngle, outsideVolume, id);
}

void AudioSourceComponent::set3DMinMaxDistanceChannel(float min, float max, int id)
{
	_audioSource->set3DMinMaxDistance(min, max, id);
}

void AudioSourceComponent::onEnable()
{
	_audioSource->resumeChannels();
}

void AudioSourceComponent::onDisable()
{
	_audioSource->pauseAllChannels();
}
