#include "..\..\Src\MotorAudio\Listener.h"
#include "..\..\Src\MotorAudio\AudioEngine.h"

#include <fmod.hpp>
#include <iostream>

Listener::Listener() : _attributes(new FMOD_3D_ATTRIBUTES()), _listenerNumber(0) {
}

Listener::~Listener() {
	delete _attributes;
}

void Listener::update()
{
	AudioEngine::getInstance()->getSystem()->set3DListenerAttributes(0, &_attributes->position, &_attributes->velocity, &_attributes->forward, &_attributes->up);
}

void Listener::setPosition(float x, float y, float z)
{
	_attributes->position = { x,y,z };
}

void Listener::setVelocity(float x, float y, float z)
{
	_attributes->velocity = { x,y,z };
}

void Listener::setForward(float x, float y, float z)
{
	_attributes->forward = { x,y,z };
}

void Listener::setUp(float x, float y, float z)
{
	_attributes->up = { x,y,z };
}

void Listener::setListenerNumber(int listenNumber)
{
	_listenerNumber = listenNumber;
}