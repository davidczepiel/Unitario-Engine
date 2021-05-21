#include "AudioEngine.h"
#include "AudioSource.h"
#include "Exceptions.h"
#include "fmod.hpp"

AudioSource::AudioSource() : _system(nullptr), _channel(), _sound(), _route()
{
	_route.push_back("");
	_position = new FMOD_VECTOR;
	_position->x = 0;
	_position->y = 0;
	_position->z = 0;
}

AudioSource::AudioSource(std::vector<std::string> const& route) : _system(nullptr), _channel(8,nullptr), _sound(), _route(route)
{
	_position = new FMOD_VECTOR;
	_position->x = 0;
	_position->y = 0;
	_position->z = 0;
	createAudio();
}

AudioSource::~AudioSource()
{
	if (_position != nullptr) delete _position;
}

void AudioSource::createAudio()
{
	_system = AudioEngine::getInstance()->getSystem();
	for (int i = 0; i < _route.size(); i++)
	{
		FMOD::Sound* audio;
		FMOD_RESULT result = _system->createSound(
			_route[i].c_str(),		// Route Path
			FMOD_DEFAULT,		// Deafult value(no loop, 2D)
			0,					// Aditional Information
			&audio);

		if (result != FMOD_OK) {
			throw EAudioSource(_route[i]);
		}
		_sound.push_back(audio);
	}
	int debug = 0;
}

void AudioSource::play(int id)
{
	FMOD_RESULT result = _system->playSound(
		_sound[id],		// buffer which sound in the channel
		0,				// channel group, 0 means ungrouped
		false,			// plays directly(no pause)
		&_channel[id]);	// return the assigned channel

	if (result != FMOD_OK)
		throw EAudioSource("There are no free channels to play the sound or the sound pointer is nullptr");
}

void AudioSource::update()
{	
	for (int i = 0; i < _channel.size(); ++i) {
		if (_channel[i] != nullptr)
			_channel[i]->set3DAttributes(_position, _velocity);
	}
}

void AudioSource::pause(int id)
{
	if (_channel[id] != nullptr) {
		bool isPause = true;
		_channel[id]->getPaused(&isPause);
		_channel[id]->setPaused(!isPause);
	}
}

void AudioSource::stop(int id)
{
	if (_channel[id] != nullptr) {
		bool isPlaying = true;
		_channel[id]->isPlaying(&isPlaying);
		if (isPlaying) _channel[id]->stop();
	}
}

void AudioSource::setLoop(int id, int loop)
{
	if (loop == 0)
		_sound[id]->setMode(FMOD_LOOP_OFF);
	else if (loop == -1)
		_sound[id]->setMode(FMOD_LOOP_NORMAL);
	else {
		_sound[id]->setMode(FMOD_LOOP_NORMAL);
		_sound[id]->setLoopCount(loop);
	}
}

void AudioSource::set3D(int id, bool stereo)
{
	if (stereo)
		_sound[id]->setMode(FMOD_3D);
	else
		_sound[id]->setMode(FMOD_2D);
}

float AudioSource::getVolumeAudio(int id) const
{
	float volume = 0.0f;
	if (_channel[id] != nullptr) {
		_channel[id]->getVolume(&volume);
	}
	return volume;
}

void AudioSource::setVolumeAudio(float v, int id)
{
	_channel[id]->setVolume(v);
}

void AudioSource::set3DConeSettings(float insideAngle, float outsideAngle, float outsideVolume, int id)
{
	_channel[id]->set3DConeSettings(insideAngle, outsideAngle, outsideVolume);
}

void AudioSource::set3DMinMaxDistance(float min, float max, int id)
{
	_channel[id]->set3DMinMaxDistance(min, max);
}

void AudioSource::setPosition(float x, float y, float z)
{
	//WIP, NOT WORKING
	//*_position = { x,y,z };
	_position->x = x;
	_position->y = y;
	_position->z = z;
}

void AudioSource::setVelocity(float x, float y, float z)
{
	*_velocity = { x,y,z };
}

void AudioSource::resumeChannels()
{
	
}

bool AudioSource::isPlaying(int id)
{
	bool isPlaying = true;
	_channel[id]->isPlaying(&isPlaying);

	return isPlaying;
}

void AudioSource::pauseAllChannels()
{
	for (int i = 0; i < _channel.size(); i++) {
		bool isPause = true;
		_channel[i]->getPaused(&isPause);
		_channel[i]->setPaused(!isPause);
	}
}