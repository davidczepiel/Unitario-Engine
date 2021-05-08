#include "OgreTextAreaOverlayElement.h"
#include "OgreStringConverter.h"
#include <OgreOverlayManager.h>

using namespace Ogre;

#ifndef __OgreText_H__
#define __OgreText_H__

class OgreText
{
public:
    OgreText();
    ~OgreText();

    void setText(char* szString);
    void setText(String szString);
    void setPos(float x, float y);
    void setCol(float R, float G, float B, float I);
private:
    OverlayManager* olm;
    OverlayContainer* panel;
    Overlay* overlay;
    TextAreaOverlayElement* textArea;
    static int init;
    String szElement;
};

int OgreText::init = 0;

#endif