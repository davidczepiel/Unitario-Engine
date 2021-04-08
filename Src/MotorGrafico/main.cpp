#include <OgreRoot.h>

void test() {
	Ogre::Root* root;
#ifdef _DEBUG
	root = new Ogre::Root("OgreDEBUG\pluginsDEBUG.cfg");
#else //RELEASE
	root = new Ogre::Root("OgreRELEASE\pluginsRELEASE.cfg");
#endif 
}