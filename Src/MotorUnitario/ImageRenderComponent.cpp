#include "ImageRenderComponent.h"
//#include "ComponentIDs.h"  

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject):Component(/*ComponentId::ImageRender*/1,gameObject),imageRender(nullptr)
{
	//Here we should create a ImageRender object ???
	//imageRender = new ImageRender();
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete imageRender;
}
