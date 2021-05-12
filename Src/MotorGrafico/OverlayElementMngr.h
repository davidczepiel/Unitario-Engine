#ifndef OGREOVERLAYELEMENTMNG_H
#define OGREOVERLAYELEMENTMNG_H

#include <string>

namespace Ogre {
	class OverlayElement;
}

class OgreOverlayElement {
	public:
		/// <summary>
		/// Class constructor
		/// </summary>
		/// <param name="elementName"> Overlay element name</param>
		OgreOverlayElement(std::string elementName);
		~OgreOverlayElement();

		/// <summary>
		/// Sets the overlay element position (1.0 = top/left)
		/// </summary>
		void setPosition(float left, float top);

		/// <summary>
		/// Sets the overlay element material
		/// </summary>
		void setMaterial(std::string materialName);

		/// <summary>
		/// Sets the overlay element width
		/// </summary>
		void setWidth(float w);

		/// <summary>
		/// Sets the overlay element height
		/// </summary>
		void setHeight(float h);

		/// <summary>
		/// Sets the overlay element visibility
		/// </summary>
		void setEnabled(bool b);
	private:
		Ogre::OverlayElement* _overlayElement;
};

#endif //!OGREOVERLAYELEMENTMNG_H