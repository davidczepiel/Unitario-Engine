#include "RigidBodyComponent.h"
//#include "ComponentIDs.h"

RigidBodyComponent::RigidBodyComponent(GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _rigidBody(nullptr)
{
	//_rigidBody = new RigidBody();
}

RigidBodyComponent::~RigidBodyComponent()
{
	delete _rigidBody; _rigidBody == nullptr;
}