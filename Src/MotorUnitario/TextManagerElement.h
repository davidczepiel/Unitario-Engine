#pragma once
#ifndef TEXTMANAGERCOMPONENT_H
#define TEXTMANAGERCOMPONENT_H

#include <string>

class OgreText;

class TextManagerElement {
	public:
		/// <summary>
		/// Class constructor
		/// </summary>
		/// <param name="overlayName">Overlay name which contains the textArea you want to manage</param>
		/// <param name="textAreaName">textArea name</param>
		TextManagerElement(std::string overlayName, std::string textAreaName);
		~TextManagerElement();

        /// <summary>
        /// Sets the text content
        /// </summary>
        /// <param name="szString"></param>
        void setText(std::string szString);

        /// <summary>
        /// Sets the text position
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        void setPosition(float x, float y);

        /// <summary>
        /// Sets the text colour in RGBA
        /// </summary>
        void setColour(float R, float G, float B, float A);

        /// <summary>
        /// Sets the text character height 
        /// </summary>
        /// <param name="h"></param>
        void setCharHeight(float h);

        /// <summary>
        /// Sets the aligment of the text
        /// </summary>
        /// <param name="aligmentType">1 -> Left | 2 -> Center | 3 -> Right</param>
        void setAlignment(int aligmentType);

        /// <summary>
        /// Enables or disables the text
        /// </summary>
        void setEnabled(bool e);

        /// <summary>
        /// Sets the font name of the text
        /// </summary>
        /// <param name="fontName"></param>
        void setFontName(std::string fontName);

        /// <summary>
        /// Sets the dimension of this element in relation to the screen (1.0 = screen width/height)
        /// </summary>
        /// <param name="w">widht</param>
        /// <param name="h">height</param>
        void setDimensions(float w, float h);
	private:
		OgreText* _ogreText;
};

#endif TEXTMANAGERCOMPONENT_H