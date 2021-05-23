#include "OverlayComponent.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "MotorGrafico/OverlayElement.h"
#include "includeLUA.h"
#include "Exceptions.h"

OverlayComponent::OverlayComponent() : Component(ComponentId::OverlayComponent),
_overlayElement(nullptr), _overlayName("")
{
}

OverlayComponent::~OverlayComponent()
{
	delete _overlayElement;
}

void OverlayComponent::awake(luabridge::LuaRef& data)
{
	_overlayElement = new OverlayElement();
	try {
		if (LUAFIELDEXIST(Name)) {
			std::string name = GETLUASTRINGFIELD(Name);
			_overlayElement->loadOverlay(name);
		}
		if (GETLUAFIELD(Hide, bool)) _overlayElement->hideOverlay();
		else _overlayElement->showOverlay();

		std::string container = "";
		if (LUAFIELDEXIST(Container) && LUAFIELDEXIST(Material))
			_overlayElement->setMaterial(GETLUASTRINGFIELD(Container), GETLUASTRINGFIELD(Material));
	}
	catch (...) {
		throw SourcePathException("The path of the overlay name, material, or the conteiner of the game object " + _gameObject->getName() + " is wrong");
	}
}

void OverlayComponent::start()
{
}

void OverlayComponent::hideOverlay(bool hide)
{
	hide ? _overlayElement->hideOverlay() : _overlayElement->showOverlay();
}

void OverlayComponent::setMaterial(std::string const& containerName, std::string const& materialName)
{
	try {
		_overlayElement->setMaterial(containerName, materialName);
	}
	catch (...) {
		throw SourcePathException("The path of the material " + materialName + " or the cointer" + containerName + "is wrong");
	}
}
