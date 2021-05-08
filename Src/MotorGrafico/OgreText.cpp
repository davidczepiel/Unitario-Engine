#include "OgreText.h"
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayManager.h>

OgreText::OgreText(std::string overlayName, std::string textAreaName)
{
    _overlayManager = Ogre::OverlayManager::getSingletonPtr();
    _textArea = static_cast<Ogre::TextAreaOverlayElement*>(_overlayManager->getOverlayElement(textAreaName));
}

OgreText::~OgreText()
{    
}

void OgreText::setText(std::string szString)
{
    _textArea->setCaption(szString);
    //_textArea->setDimensions(1.0f, 1.0f);
    //_textArea->setMetricsMode(Ogre::GMM_RELATIVE);
    //_textArea->setFontName("Arial");
    //_textArea->setCharHeight(0.03f);
}

void OgreText::setPos(float x, float y)
{
    _textArea->setPosition(x, y);
}

void OgreText::setCol(float R, float G, float B, float I)
{
    _textArea->setColour(Ogre::ColourValue(R, G, B, I));
}
