#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

//#include "MotorFisico/RigidBody.h"
#include "Component.h"

class GameObject;

class RigidBodyComponent : public Component {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	RigidBodyComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~RigidBodyComponent();

	inline void method1() { /*_rigidBody->method1();*/ }

	inline void method2() { /*_rigidBody->method2();*/ }

	inline void method3() { /*_rigidBody->method3();*/ }

	inline void method4() { /*_rigidBody->method4();*/ }

	inline void method5() { /*_rigidBody->method5();*/ }

	/// <summary>
	/// This method sets the parameter x to the rigidBody Property
	/// </summary>
	inline void setParameter1(float x) {/*_rigidBody->setParameter1(x);*/ }

	/// <summary>
	/// This method sets the parameters x and y to the rigidBody Properties
	/// </summary>
	inline void setParameter2(float x, float y) {/*_rigidBody->setParameter2(x,y);*/ }

	/// <summary>
	/// This method sets the parameter x, y and z to the rigidBody Properties
	/// </summary>
	inline void setParameter3(float x, float y, float z) {/*_rigidBody->setParameter3(x,y,z);*/ }

	/// <summary>
	/// This method return the parameter 1 from the rigidBody
	/// </summary>
	inline float getParameter1() { /*return _rigidBody->getParameter1();*/ return 0; };

	/// <summary>
	/// This method return the parameter 2 from the rigidBody
	/// </summary>
	inline float getParameter2() { /*return _rigidBody->getParameter2();*/ return 0; };

private:
	Component* _rigidBody;
};
#endif // !RIGIDBODYCOMPONENT_H