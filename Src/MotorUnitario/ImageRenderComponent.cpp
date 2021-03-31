#include "ImageRenderComponent.h"
//#include "ComponentIDs.h"  

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject):Component(/*ComponentId::ImageRender*/1,gameObject),imageRender(nullptr)
{
}

ImageRenderComponent::~ImageRenderComponent()
{
}
