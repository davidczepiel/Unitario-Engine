#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

class GameObject;
class Collider;
class BoxCollider;
class SphereCollider;
class CapsuleCollider;

class ColliderComponent : public Component {
public:

	static void gameObjectsCollision(GameObject* thisGO, GameObject* otherGO);
	static void gameObjectTriggered(GameObject* thisGO, GameObject* otherGO);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ColliderComponent();

	void setCollider();

	void setTrigger();

protected:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	ColliderComponent(int id, GameObject* gameObject);

	Collider* _collider;
};

#endif // !COLLIDERCOMPONENT_H
//////////////////////////////////////////////////////

class BoxColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	BoxColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~BoxColliderComponent();

	void setScale(int width, int heigh, int depth);
};

/////////////////////////////////////////////////////////

class SphereColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	SphereColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~SphereColliderComponent();

	void setScale(int radius);
};

////////////////////////////////////////////////////

class CapsuleColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	CapsuleColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~CapsuleColliderComponent();

	void setScale(int radius, int length);
};