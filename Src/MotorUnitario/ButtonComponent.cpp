#include "ButtonComponent.h"
#include "ComponentIDs.h"
#include "MotorGrafico/OverlayElement.h"
#include "MouseInput.h"
#include "KeyCodes.h"
#include <SDL.h>
#include "includeLUA.h"


ButtonComponent::ButtonComponent() :Component(ComponentId::ButtonComponent),
_button(nullptr), _callback(nullptr), _callbackParam(nullptr), _overlayName(), _containerName(),
_defaultMaterial(), _hoverMaterial(), _pressMaterial(), _active(true)
{
}

//
//ButtonComponent::ButtonComponent(GameObject* gO, CallBackOnClick* callback, std::string const& overlayName,
//	std::string const& containerName, std::string const& defaultMaterial, std::string const& passingMaterial,
//	std::string const& pressMaterial, void* callbackParam) : Component(ComponentId::ButtonComponent, gO),
//	_button(nullptr), _callback(callback), _callbackParam(callbackParam), _overlayName(overlayName), _containerName(containerName), _defaultMaterial(defaultMaterial),
//	_hoverMaterial(passingMaterial), _pressMaterial(pressMaterial), _active(true)
//{
//}

ButtonComponent::~ButtonComponent()
{
	delete _button;
}

void ButtonComponent::awake(luabridge::LuaRef& data)
{
	if (LUAFIELDEXIST(OverLayName))
		_overlayName = data["OverLayName"].cast<std::string>();
	if (LUAFIELDEXIST(Active))
		_active = data["Active"].cast<bool>();
	if (LUAFIELDEXIST(ContainerName))
		_containerName = data["ContainerName"].cast<std::string>();
	if (LUAFIELDEXIST(DefaultMaterial))
		_defaultMaterial = data["DefaultMaterial"].cast<std::string>();
	if (LUAFIELDEXIST(HoverMaterial))
		_hoverMaterial = data["HoverMaterial"].cast<std::string>();
	if (LUAFIELDEXIST(PressMaterial))
		_pressMaterial = data["PressMaterial"].cast<std::string>();

	std::cout << "ButtonComponent loaded" << std::endl;
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
			if (mouse->isMouseButtonDown(MouseButton::LEFT)) {
				//Change the material for feedback
				_button->setMaterial(_containerName, _pressMaterial);
				//Calls the function
				_callback(_callbackParam);
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

void ButtonComponent::onEnable()
{
	hideShowButton(true);
}

void ButtonComponent::onDisable()
{
	hideShowButton(false);
}
