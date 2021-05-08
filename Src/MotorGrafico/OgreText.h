#ifndef __OgreText_H__
#define __OgreText_H__

#include <string>

namespace Ogre {
    class OverlayManager;
    class OverlayContainer;
    class TextAreaOverlayElement;
}

class OgreText
{
public:
    OgreText(std::string overlayName, std::string textAreaName);
    ~OgreText();

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
    void setPos(float x, float y);

    /// <summary>
    /// Sets the text colour in RGBA
    /// </summary>
    void setCol(float R, float G, float B, float I);
private:
    Ogre::OverlayManager* _overlayManager;
    Ogre::TextAreaOverlayElement* _textArea;
};

#endif