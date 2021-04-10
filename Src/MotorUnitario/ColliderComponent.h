#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

//#include "MotorFisico/Collider.h"
#include "Component.h"

class GameObject;

class ColliderComponent : public Component {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	ColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ColliderComponent();

	inline void method1() { /*_collider->method1();*/ }

	inline void method2() { /*_collider->method2();*/ }

	inline void method3() { /*_collider->method3();*/ }

	inline void method4() { /*_collider->method4();*/ }

	inline void method5() { /*_collider->method5();*/ }

	/// <summary>
	/// This method sets the parameter x to the collider Property
	/// </summary>
	inline void setParameter1(float x) {/*_collider->setParameter1(x);*/ }

	/// <summary>
	/// This method sets the parameters x and y to the collider Properties
	/// </summary>
	inline void setParameter2(float x, float y) {/*_collider->setParameter2(x,y);*/ }

	/// <summary>
	/// This method sets the parameter x, y and z to the collider Properties
	/// </summary>
	inline void setParameter3(float x, float y, float z) {/*_collider->setParameter3(x,y,z);*/ }

	/// <summary>
	/// This method return the parameter 1 from the collider
	/// </summary>
	inline float getParameter1() { /*return _collider->getParameter1();*/ return 0; };

	/// <summary>
	/// This method return the parameter 2 from the collider
	/// </summary>
	inline float getParameter2() { /*return _collider->getParameter2();*/ return 0; };

private:
	Component* _collider;
};
#endif // !COLLIDERCOMPONENT_H