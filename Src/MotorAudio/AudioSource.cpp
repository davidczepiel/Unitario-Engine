#include "..\..\Src\MotorAudio\AudioSource.h"
#include "..\..\Src\MotorAudio\AudioEngine.h"
#include "..\..\Src\MotorAudio\Exceptions.h"


AudioSource::AudioSource() : _system(nullptr), _channel(nullptr), _sound(nullptr), _volume(0.5f), _isLoop(false), _rute("")
{

}

AudioSource::AudioSource(std::string rute, bool loop): _system(nullptr), _channel(nullptr), _sound(nullptr), _volume(0.5f), _isLoop(loop), _rute(rute)
{
}

AudioSource::~AudioSource()
{
}

void AudioSource::init()
{
	_system = AudioEngine::getInstance()->getSystem();

	FMOD_RESULT result = _system->createSound(
		_rute.c_str(), // path al archivo de sonido
		FMOD_DEFAULT, // valores (por defecto en este caso: sin loop, 2D)
		0, // informacion adicional (nada en este caso)
		&_sound);

	if (result != FMOD_OK) {
		throw EAudioSource("Error loading sound");
	}	
}

bool AudioSource::play(int n)
{
	FMOD_RESULT result = _system->playSound(
		_sound, // buffer que se "engancha" a ese canal
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false, // arranca sin "pause" (se reproduce directamente)
		&_channel); // devuelve el canal que asigna
		// el sonido ya se esta reproduciendo

	if (result == FMOD_OK) return true;
	throw EAudioSource("There are no free channels to play the sound or the sound pointer is nullptr");
}

void AudioSource::pause()
{	
	if (_channel != nullptr) {
		bool* isPause;
		_channel->getPaused(isPause);
		_channel->setPaused(!isPause);
	}
}

void AudioSource::stop()
{
	if (_channel != nullptr) {
		bool* isPlaying;
		_channel->isPlaying(isPlaying);
		if (isPlaying) _channel->stop();
	}
}