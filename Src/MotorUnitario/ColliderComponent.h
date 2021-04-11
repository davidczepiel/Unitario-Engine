#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

class GameObject;
//class Collider;

class ColliderComponent : public Component {
public:

	ColliderComponent();

	/// <summary>
	/// Contructor of the class
	/// </summary>
	ColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ColliderComponent();

	void method1();

	void method2();

	void method3();

	void method4();

	void method5();

	/// <summary>
	/// This method sets the parameter x to the collider Property
	/// </summary>
	void setParameter1(float x);

	/// <summary>
	/// This method sets the parameters x and y to the collider Properties
	/// </summary>
	void setParameter2(float x, float y);

	/// <summary>
	/// This method sets the parameter x, y and z to the collider Properties
	/// </summary>
	void setParameter3(float x, float y, float z);

	/// <summary>
	/// This method return the parameter 1 from the collider
	/// </summary>
	float getParameter1();

	/// <summary>
	/// This method return the parameter 2 from the collider
	/// </summary>
	float getParameter2();

private:
	Component* _collider;
};
#endif // !COLLIDERCOMPONENT_H