#include "TextManagerElement.h"
#include "MotorGrafico/OgreText.h"
#include "Exceptions.h"

TextManagerElement::TextManagerElement(std::string textAreaName)
{
	try {
		_ogreText = new OgreText(textAreaName);
	}
	catch (...) {
		throw SourcePathException("Overlay Text with the path " + textAreaName + "doesn't exist");
	}
}

TextManagerElement::~TextManagerElement()
{
}

void TextManagerElement::setText(std::string szString)
{
	_ogreText->setText(szString);
}

void TextManagerElement::setPosition(float x, float y)
{
	_ogreText->setPosition(x, y);
}

void TextManagerElement::setColour(float R, float G, float B, float A)
{
	_ogreText->setColour(R, G, B, A);
}

void TextManagerElement::setCharHeight(float h)
{
	_ogreText->setCharHeight(h);
}

void TextManagerElement::setAlignment(int aligmentType)
{
	_ogreText->setAlignment(aligmentType);
}

void TextManagerElement::setEnabled(bool e)
{
	_ogreText->setEnabled(e);
}

void TextManagerElement::setFontName(std::string fontName)
{
	_ogreText->setFontName(fontName);
}

void TextManagerElement::setDimensions(float w, float h)
{
	_ogreText->setDimensions(w, h);
}
