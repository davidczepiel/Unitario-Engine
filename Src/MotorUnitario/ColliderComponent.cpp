#include "ColliderComponent.h"
//#include "ComponentIDs.h"

ColliderComponent::ColliderComponent(GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _collider(nullptr)
{
	//_collider = new Collider();
}

ColliderComponent::~ColliderComponent()
{
	delete _collider; _collider == nullptr;
}