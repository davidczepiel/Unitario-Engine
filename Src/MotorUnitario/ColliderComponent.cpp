#include "ColliderComponent.h"
//#include "ComponentIDs.h"

ColliderComponent::ColliderComponent() : Component(7),_collider(nullptr)
{
}

ColliderComponent::ColliderComponent(GameObject* gameObject) : Component(/*ComponentId::ImageRender*/1, gameObject), _collider(nullptr)
{
	//_collider = new Collider();
}

ColliderComponent::~ColliderComponent()
{
	delete _collider; _collider == nullptr;
}

void ColliderComponent::method1() {
	/*_collider->method1();*/
}

void ColliderComponent::method2() {
	/*_collider->method2();*/
}

void ColliderComponent::method3() {
	/*_collider->method3();*/
}

void ColliderComponent::method4() {
	/*_collider->method4();*/
}

void ColliderComponent::method5() {
	/*_collider->method5();*/
}

void ColliderComponent::setParameter1(float x) {
	/*_collider->setParameter1(x);*/
}

void ColliderComponent::setParameter2(float x, float y) {
	/*_collider->setParameter2(x,y);*/
}

void ColliderComponent::setParameter3(float x, float y, float z) {
	/*_collider->setParameter3(x,y,z);*/
}

float ColliderComponent::getParameter1() {
	/*return _collider->getParameter1();*/
	return 0;
};

float ColliderComponent::getParameter2() {
	/*return _collider->getParameter2();*/
	return 0;
};