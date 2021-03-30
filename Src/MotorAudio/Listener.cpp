#include "..\..\Src\MotorAudio\Listener.h"
#include "..\..\Src\MotorAudio\AudioEngine.h"

#include "fmod.h"

Listener::Listener() : _attributes(), _listenerNumber(0) {

}
Listener::~Listener() {

}
void Listener::update()
{
	AudioEngine::getInstance()->getSystem()->set3DListenerAttributes(_listenerNumber, &_attributes.position, &_attributes.velocity, &_attributes.forward, &_attributes.up);
}
