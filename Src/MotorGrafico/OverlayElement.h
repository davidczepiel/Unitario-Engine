#pragma once

#include <string>

namespace Ogre {
	class Overlay;
}

class OverlayElement {
public:
	/// <summary>
	/// Class constructor
	/// </summary>
	/// <param name="overlayName"> Overlay name (in .overlay)</param>
	OverlayElement(std::string const& overlayName);
	~OverlayElement();

	/// <summary>
	/// Shows the overlay
	/// </summary>
	void showOverlay();

	/// <summary>
	/// Hides the overlay
	/// </summary>
	void hideOverlay();

	/// <summary>
	/// Sets the material of an overlays child
	/// </summary>
	/// <param name="containerName"> Name of the overlays child </param>
	/// <param name="materialName"> New material name </param>
	void setMaterial(std::string const& containerName, std::string const& materialName);
	/// <summary>
	/// Gets the position of the Overlay Element
	/// </summary>
		/// <param name="containerName"> Name of the overlays child </param>
	std::pair<int, int> getPosition(std::string const& containerName);
	/// <summary>
	/// Gets the Width of the Overlay Element
	/// </summary>
	/// <param name="containerName"> Name of the overlays child </param>
	std::pair<int, int> getSize(std::string const& containerName);

protected:
	Ogre::Overlay* _overlay;
private:
	/// <summary>
	/// private method to load an overlay from a .overlay file
	/// </summary>
	/// <param name="overlayName"></param>
	void loadOverlay(std::string const& overlayName);
};