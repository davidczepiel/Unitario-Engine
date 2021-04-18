#include "ButtonComponent.h"
#include "ComponentIDs.h"
#include "MotorGrafico/OverlayElement.h"
#include "MouseInput.h"

ButtonComponent::ButtonComponent(GameObject* gO):Component(ComponentId::ButtonComponent, gO), _button(nullptr), _callback(nullptr),_overlayName(),_containerName(),
_defaultMaterial(), _hoverMaterial(), _pressMaterial(), _active(true)
{
}

ButtonComponent::ButtonComponent(GameObject* gO, CallBackOnClick* callback, std::string const& overlayName, std::string const& containerName, std::string const& defaultMaterial, std::string const& passingMaterial, std::string const& pressMaterial):
	Component(ComponentId::ButtonComponent, gO), _button(nullptr), _callback(callback), _overlayName(overlayName),_containerName(containerName), _defaultMaterial(defaultMaterial),
	_hoverMaterial(passingMaterial), _pressMaterial(pressMaterial), _active(true)
{
}

ButtonComponent::~ButtonComponent()
{
	delete _button;
}

void ButtonComponent::start()
{
	_button = new OverlayElement(_overlayName);
}

void ButtonComponent::update()
{
	if (_active) {
		//Get the position of the mouse and button
		MouseInput* mouse = MouseInput::getInstance();
		std::pair<int, int> buttonPos = _button->getPosition(_containerName);
		std::pair<int, int> buttonSize = _button->getSize(_containerName);
		std::pair<int, int> mousePos;
		mousePos.first = mouse->getMousePos()[0];
		mousePos.second = mouse->getMousePos()[1];

		SDL_Point mousePosition = { mousePos.first, mousePos.second };
		SDL_Rect buttonRect = { buttonPos.first, buttonPos.second, buttonSize.first, buttonSize.second };

		//If the mouse Position is in the button rect
		if (SDL_PointInRect(&mousePosition, &buttonRect)) {
			//Change the material for feedback
			_button->setMaterial(_containerName, _hoverMaterial);
			//If the mouse is also down
			if (mouse->isMouseButtonDown(MouseInput::MOUSEBUTTON::LEFT)) {
				//Change the material for feedback
				_button->setMaterial(_containerName, _pressMaterial);
				//Calls the function
				_callback();
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
		_button->showOverlay();
	else 
		_button->hideOverlay();
}


