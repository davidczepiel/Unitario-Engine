#include "OverlayComponent.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "MotorGrafico/OverlayElement.h"

OverlayComponent::OverlayComponent() : Component(ComponentId::OverlayComponent),
_overlayElement(nullptr)
{
}

OverlayComponent::OverlayComponent(GameObject* go) : Component(ComponentId::OverlayComponent, go),
_overlayElement(nullptr)
{
}

OverlayComponent::OverlayComponent(GameObject* go, std::string const& overlayName) : Component(ComponentId::OverlayComponent, go)
{
	_overlayElement = new OverlayElement(overlayName);
}

OverlayComponent::~OverlayComponent()
{
	delete _overlayElement;
}

void OverlayComponent::start()
{
	_overlayElement = new OverlayElement(_overlayName);
}

void OverlayComponent::hideOverlay(bool hide)
{
	hide ? _overlayElement->hideOverlay() : _overlayElement->showOverlay();
}

void OverlayComponent::setMaterial(std::string const& containerName, std::string const& materialName)
{
	_overlayElement->setMaterial(containerName, materialName);
}
