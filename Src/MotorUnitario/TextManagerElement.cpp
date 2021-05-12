#include "TextManagerElement.h"
#include "MotorGrafico/OgreText.h"

TextManagerElement::TextManagerElement(std::string textAreaName)
{
	_ogreText = new OgreText(textAreaName);
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
