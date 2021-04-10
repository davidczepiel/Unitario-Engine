#include "ImageRenderComponent.h"
//#include "ComponentIDs.h"  
#include <iostream>

ImageRenderComponent::ImageRenderComponent(): Component(2),imageRender(nullptr)
{
	std::cout << "IMAGERENDER CREADO\n";
	imageRender = new ImageRender();
}

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject):Component(/*ComponentId::ImageRender*/1,gameObject),imageRender(nullptr)
{	
	imageRender = new ImageRender();
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete imageRender; imageRender == nullptr;
}
