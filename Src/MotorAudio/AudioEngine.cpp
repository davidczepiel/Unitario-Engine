#include "..\..\Src\MotorAudio\AudioEngine.h"

#include "fmod.h"

AudioEngine* AudioEngine::_instance = nullptr;

AudioEngine::~AudioEngine()
{
	if(_system != nullptr)
		_system->release();
}

AudioEngine* AudioEngine::getInstance()
{
	if (_instance == nullptr) {
		_instance = new AudioEngine();
	}
	return _instance;
}

void AudioEngine::init() {
	FMOD_RESULT result;
	result = FMOD::System_Create(&_system); // Create the System Objects
	// 128 channels (max number that we can use)
	result = _system->init(128, FMOD_INIT_NORMAL, 0); //Fmod Initialization

	if (result != FMOD_OK) {
		//TO DO
	}
}

void AudioEngine::update()
{
	_system->update();
}

void AudioEngine::release()
{
	if(_system != nullptr)
		_system->release();
}

AudioEngine::AudioEngine(): _system(nullptr){

}
