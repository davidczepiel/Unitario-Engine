#include "ButtonComponent.h"
#include "ComponentIDs.h"
#include "MotorGrafico/OverlayElement.h"
#include "AudioSourceComponent.h"
#include "MouseInput.h"
#include "KeyCodes.h"
#include <SDL.h>
#include "includeLUA.h"
#include "GameObject.h"
#include "Engine.h"
#include "Exceptions.h"


ButtonComponent::ButtonComponent() :Component(ComponentId::ButtonComponent),
_button(nullptr), _callback(nullptr), _audio(nullptr), _callbackParam(nullptr), _overlayName(), _containerName(),
_defaultMaterial(), _hoverMaterial(), _pressMaterial(), _active(true)
{
}

ButtonComponent::~ButtonComponent()
{
	delete _button;
}

void ButtonComponent::awake(luabridge::LuaRef& data)
{
	if (LUAFIELDEXIST(OverLayName))
		_overlayName = GETLUASTRINGFIELD(OverLayName);
	if (LUAFIELDEXIST(Active))
		_active = GETLUAFIELD(Active, bool);
	if (LUAFIELDEXIST(ContainerName))
		_containerName = GETLUASTRINGFIELD(ContainerName);
	if (LUAFIELDEXIST(DefaultMaterial))
		_defaultMaterial = GETLUASTRINGFIELD(DefaultMaterial);
	if (LUAFIELDEXIST(HoverMaterial))
		_hoverMaterial = GETLUASTRINGFIELD(HoverMaterial);
	if (LUAFIELDEXIST(PressMaterial))
		_pressMaterial = GETLUASTRINGFIELD(PressMaterial);

	std::cout << "ButtonComponent loaded" << std::endl;
}

void ButtonComponent::start()
{
	_button = new OverlayElement();
	try {
		_button->loadOverlay(_overlayName);
	}
	catch (...) {
		throw SourcePathException("Overlay could not be loaded, the overlay " + _overlayName + "doesn't exist");
	}

	_audio = GETCOMPONENT(AudioSourceComponent, ComponentId::AudioSource);
}

void ButtonComponent::update()
{
	if (_active) {
		//Get the position of the mouse and button
		MouseInput* mouse = MouseInput::getInstance();
		std::pair<int, int> buttonPos = _button->getPosition(_containerName);
		std::pair<int, int> buttonSize = _button->getSize(_containerName);
		std::pair<int, int> mousePos;
		mousePos.first = mouse->getMousePos()[0] * Engine::getInstance()->getWindowSize().first;
		mousePos.second = mouse->getMousePos()[1] * Engine::getInstance()->getWindowSize().second;

		SDL_Point mousePosition = { mousePos.first, mousePos.second };
		SDL_Rect buttonRect = { buttonPos.first, buttonPos.second, buttonSize.first, buttonSize.second };

		//If the mouse Position is in the button rect
		if (SDL_PointInRect(&mousePosition, &buttonRect)) {
			//Change the material for feedback
			_button->setMaterial(_containerName, _hoverMaterial);
			//If the mouse is also down
			if (mouse->isMouseButtonDown(MouseButton::LEFT)) {
				//Change the material for feedback
				_button->setMaterial(_containerName, _pressMaterial);
				//Calls the function
				_callback(_callbackParam);

				if (_audio != nullptr) _audio->playAudio(0);
			}
		}
		else {
			_button->setMaterial(_containerName, _defaultMaterial);
		}
	}
}

void ButtonComponent::hideShowButton(bool show)
{
	_active = show;
	if (show)
		_button->showOverlay(_containerName);
	else
		_button->hideOverlay(_containerName);
}

void ButtonComponent::onEnable()
{
	hideShowButton(true);
}

void ButtonComponent::onDisable()
{
	hideShowButton(false);
}
