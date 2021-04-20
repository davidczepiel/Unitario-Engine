#include "ImageRenderComponent.h"
#include "ComponentIDs.h"

ImageRender::BillboardOrigin getBillboardOrigin(std::string cmp);
ImageRender::BillboardType getBillboardType(std::string cmp);
ImageRender::BillboardRotationType getBillboardRotationType(std::string cmp);

void ImageRenderComponent::awake(luabridge::LuaRef& data)
{
	imageRender->setDefaultDimensions(data["DefaultDimension"]["W"].cast<float>(), data["DefaultDimension"]["H"].cast<float>());
	imageRender->setMaterialName(data["MaterialName"].cast<std::string>());
	imageRender->setVisible(data["Visible"].cast<bool>());

	imageRender->setBillboardOrigin(getBillboardOrigin(data["BillboardOrigin"].cast<std::string>()));
	imageRender->setBillboardType(getBillboardType(data["BillboardType"].cast<std::string>()));
	imageRender->setBillboardRotationType(getBillboardRotationType(data["BillboardRotationType"].cast<std::string>()));

	imageRender->setScale(data["Scale"]["X"].cast<float>(), data["Scale"]["Y"].cast<float>(), data["Scale"]["Z"].cast<float>());
	imageRender->setRotation(data["Rotation"]["X"].cast<float>(), data["Rotation"]["Y"].cast<float>(),
		data["Rotation"]["Z"].cast<float>(), data["Rotation"]["Angle"].cast<float>());
}

ImageRenderComponent::ImageRenderComponent() : Component(ComponentId::ImageRender), imageRender(nullptr)
{
	imageRender = new ImageRender();
}

ImageRenderComponent::ImageRenderComponent(GameObject* gameObject) :Component(ComponentId::ImageRender, gameObject), imageRender(nullptr)
{
	imageRender = new ImageRender();
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete imageRender; imageRender == nullptr;
}

ImageRender::BillboardOrigin getBillboardOrigin(std::string cmp) {
	
	if (cmp == "BBO_TOP_LEFT")
		return ImageRender::BillboardOrigin::BBO_TOP_LEFT;
	else if (cmp == "BBO_TOP_CENTER")
		return ImageRender::BillboardOrigin::BBO_TOP_CENTER;
	else if (cmp == "BBO_TOP_RIGHT")
		return ImageRender::BillboardOrigin::BBO_TOP_RIGHT;
	else if (cmp == "BBO_CENTER_LEFT")
		return ImageRender::BillboardOrigin::BBO_CENTER_LEFT;
	else if (cmp == "BBO_CENTER")
		return ImageRender::BillboardOrigin::BBO_CENTER;
	else if (cmp == "BBO_CENTER_RIGHT")
		return ImageRender::BillboardOrigin::BBO_CENTER_RIGHT;
	else if (cmp == "BBO_BOTTOM_LEFT")
		return ImageRender::BillboardOrigin::BBO_BOTTOM_LEFT;
	else if (cmp == "BBO_BOTTOM_CENTER")
		return ImageRender::BillboardOrigin::BBO_BOTTOM_CENTER;
	else if (cmp == "BBO_BOTTOM_RIGHT")
		return ImageRender::BillboardOrigin::BBO_BOTTOM_RIGHT;
}

ImageRender::BillboardType getBillboardType(std::string cmp)
{
	if (cmp == "BBT_POINT")
		return ImageRender::BillboardType::BBT_POINT;
	else if (cmp == "BBT_ORIENTED_COMMON")
		return ImageRender::BillboardType::BBT_ORIENTED_COMMON;
	else if (cmp == "BBT_ORIENTED_SELF")
		return ImageRender::BillboardType::BBT_ORIENTED_SELF;
	else if (cmp == "BBT_PERPENDICULAR_COMMON")
		return ImageRender::BillboardType::BBT_PERPENDICULAR_COMMON;
	else if (cmp == "BBT_PERPENDICULAR_SELF")
		return ImageRender::BillboardType::BBT_PERPENDICULAR_SELF;
}

ImageRender::BillboardRotationType getBillboardRotationType(std::string cmp)
{
	if (cmp == "BBR_VERTEX")
		return ImageRender::BillboardRotationType::BBR_VERTEX;
	else if (cmp == "BBR_TEXCOORD")
		return ImageRender::BillboardRotationType::BBR_TEXCOORD;
}

