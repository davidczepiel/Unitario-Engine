#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

//#include "MotorFisico/RigidBody.h"
#include "Component.h"

class GameObject;
//class RigidBody

class RigidBodyComponent : public Component {
public:

	RigidBodyComponent();

	/// <summary>
	/// Contructor of the class
	/// </summary>
	RigidBodyComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~RigidBodyComponent();

	void method1();

	void method2();

	void method3();

	void method4();

	void method5();

	/// <summary>
	/// This method sets the parameter x to the rigidBody Property
	/// </summary>
	void setParameter1(float x);

	/// <summary>
	/// This method sets the parameters x and y to the rigidBody Properties
	/// </summary>
	void setParameter2(float x, float y);

	/// <summary>
	/// This method sets the parameter x, y and z to the rigidBody Properties
	/// </summary>
	void setParameter3(float x, float y, float z);

	/// <summary>
	/// This method return the parameter 1 from the rigidBody
	/// </summary>
	float getParameter1();

	/// <summary>
	/// This method return the parameter 2 from the rigidBody
	/// </summary>
	float getParameter2();

private:
	Component* _rigidBody;
};
#endif // !RIGIDBODYCOMPONENT_H