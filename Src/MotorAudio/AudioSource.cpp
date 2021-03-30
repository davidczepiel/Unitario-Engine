#include "..\..\Src\MotorAudio\AudioSource.h"
#include "..\..\Src\MotorAudio\AudioEngine.h"
//#include "..\..\Src\MotorAudio\Exceptions.h"


AudioSource::AudioSource() : _system(nullptr), _channel(nullptr), _sound(), _route("")
{

}

AudioSource::AudioSource(std::string route, bool loop): _system(nullptr), _channel(nullptr), _sound(), _route(route)
{
}

AudioSource::~AudioSource()
{
}

void AudioSource::createAudio()
{
	_system = AudioEngine::getInstance()->getSystem();
	FMOD::Sound* audio;
	FMOD_RESULT result = _system->createSound(
		_route.c_str(),		// Route Path
		FMOD_DEFAULT,		// Deafult value(no loop, 2D)
		0,					// Aditional Information
		&audio);

	if (result != FMOD_OK) {
		//throw EAudioSource("Error loading sound");
	}	
	_sound.push_back(audio);
}

bool AudioSource::play(int id)
{
	FMOD_RESULT result = _system->playSound(
		_sound[id],		// buffer which sound in the channel
		0,				// channel group, 0 means ungrouped
		false,			// plays directly(no pause)
		&_channel);		// return the assigned channel 
		
	if (result == FMOD_OK) return true;
	//throw EAudioSource("There are no free channels to play the sound or the sound pointer is nullptr");
}

void AudioSource::update()
{
	_channel->set3DAttributes(_position, _velocity);
}

void AudioSource::pause()
{	
	if (_channel != nullptr) {
		bool isPause =  true;
		_channel->getPaused(&isPause);
		_channel->setPaused(!isPause);
	}
}

void AudioSource::stop()
{
	if (_channel != nullptr) {
		bool isPlaying = true;
		_channel->isPlaying(&isPlaying);
		if (isPlaying) _channel->stop();
	}
}

void AudioSource::setLoop(int id, int loop)
{
	if (loop == 0)
		_sound[id]->setMode(FMOD_LOOP_OFF);	
	else if (loop = -1) 
		_sound[id]->setMode(FMOD_LOOP_NORMAL);
	else {
		_sound[id]->setMode(FMOD_LOOP_NORMAL);
		_sound[id]->setLoopCount(loop);
	}
}

void AudioSource::set3D(int id, bool stereo)
{
	if(stereo)
		_sound[id]->setMode(FMOD_3D);
	else
		_sound[id]->setMode(FMOD_2D);
}

float AudioSource::getVolume() const
{
	float volume = 0.0f;
	if (_channel != nullptr) {
		_channel->getVolume(&volume);
	}
	return volume;
}
