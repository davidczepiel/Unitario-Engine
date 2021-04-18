#pragma once

#include <string>

namespace Ogre {
	class Overlay;
}

class OverlayElement {
public:
	OverlayElement(std::string const& overlayName);
	~OverlayElement();

	void showOverlay();
	void hideOverlay();
	void setMaterial(std::string const& containerName, std::string const& materialName);
protected:
	Ogre::Overlay* _overlay;
private:
	void loadOverlay(std::string const& overlayName);
};