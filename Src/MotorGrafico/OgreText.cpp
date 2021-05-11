#include "OgreText.h"
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayManager.h>

OgreText::OgreText(std::string textAreaName)
{
    _textArea = static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->getOverlayElement(textAreaName));
}

OgreText::~OgreText()
{    
}

void OgreText::setText(std::string szString)
{
    _textArea->setCaption(szString);
}

void OgreText::setPosition(float x, float y)
{
    _textArea->setPosition(x, y);
}

void OgreText::setColour(float R, float G, float B, float I)
{
    _textArea->setColour(Ogre::ColourValue(R, G, B, I));
}

void OgreText::setCharHeight(float h)
{
    _textArea->setCharHeight(h);
}

void OgreText::setAlignment(int aligmentType)
{
    switch (aligmentType)
    {
    case 1:
        _textArea->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);
        break;
    case 2:
        _textArea->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
        break;
    case 3:
        _textArea->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
        break;
    default:
        break;
    }
}

void OgreText::setEnabled(bool e)
{
    _textArea->setEnabled(e);
}

void OgreText::setFontName(std::string fontName)
{
    _textArea->setFontName(fontName);
}

void OgreText::setDimensions(float w, float h)
{
    _textArea->setDimensions(w, h);
}
