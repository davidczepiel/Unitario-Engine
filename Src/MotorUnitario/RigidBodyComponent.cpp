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

void RigidBodyComponent::method1() {
	/*_rigidBody->method1();*/
}

void RigidBodyComponent::method2() {
	/*_rigidBody->method2();*/
}

void RigidBodyComponent::method3() {
	/*_rigidBody->method3();*/
}

void RigidBodyComponent::method4() {
	/*_rigidBody->method4();*/
}

void RigidBodyComponent::method5() {
	/*_rigidBody->method5();*/
}

void RigidBodyComponent::setParameter1(float x) {
	/*_rigidBody->setParameter1(x);*/
}

void RigidBodyComponent::setParameter2(float x, float y) {
	/*_rigidBody->setParameter2(x,y);*/
}

void RigidBodyComponent::setParameter3(float x, float y, float z) {
	/*_rigidBody->setParameter3(x,y,z);*/
}

float RigidBodyComponent::getParameter1() {
	/*return _rigidBody->getParameter1();*/
	return 0;
}

float RigidBodyComponent::getParameter2() {
	/*return _rigidBody->getParameter2();*/
	return 0;
}