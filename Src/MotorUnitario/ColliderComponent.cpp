#include "ColliderComponent.h"
#include "MotorFisico/Collider.h"
#include "GameObject.h"
//#include "ComponentIDs.h"

ColliderComponent::ColliderComponent(int id, GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _collider(nullptr)
{
	//_collider = new Collider();
}

ColliderComponent::~ColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void ColliderComponent::setCollider() {
	/*_collider->method1();*/
}

void ColliderComponent::setTrigger() {
	/*_collider->method2();*/
}

//////////////////

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject) : ColliderComponent(/*ComponentId::ImageRender*/1, gameObject)
{
	_collider = new BoxCollider(1, 1, 1, false);
}

BoxColliderComponent::~BoxColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void BoxColliderComponent::setScale(int width, int heigh, int depth)
{
	static_cast<BoxCollider*>(_collider)->setScale(width, heigh, depth);
}

////////////////////////////////////////////
//
//SphereColliderComponent::SphereColliderComponent(GameObject* gameObject) : ColliderComponent(/*ComponentId::ImageRender*/1, gameObject)
//{
//	_collider = new SphereCollider(1, false);
//}
//
//SphereColliderComponent::~SphereColliderComponent()
//{
//	delete _collider; _collider == nullptr;
//}
//
//void SphereColliderComponent::setScale(int radius)
//{
//	static_cast<SphereCollider*>(_collider)->setScale(radius);
//}
//
/////////////////////////////////////////////////////////
//
//CapsuleColliderComponent::CapsuleColliderComponent(GameObject* gameObject) : ColliderComponent(/*ComponentId::ImageRender*/1, gameObject)
//{
//	_collider = new CapsuleCollider(1, 1, false);
//}
//
//CapsuleColliderComponent::~CapsuleColliderComponent()
//{
//	delete _collider; _collider == nullptr;
//}
//
//void CapsuleColliderComponent::setScale(int radius, int length)
//{
//	static_cast<CapsuleCollider*>(_collider)->setScale(radius, length);
//}