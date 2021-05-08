#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

class GameObject;
class Collider;
class BoxCollider;
class SphereCollider;
class CapsuleCollider;
class Vector3;

#define VEC3_TO_TUPLE(vec) std::tuple<float, float, float>(vec.getX(), vec.getY(), vec.getZ())
#define TUPLE_TO_VEC3(tuple) Vector3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))

class ColliderComponent : public Component {
public:

	/// <summary>
	/// Callback for gameobject collision
	/// </summary>
	/// <param name="thisGO"></param>
	/// <param name="otherGO"></param>
	static void gameObjectsCollision(GameObject* thisGO, GameObject* otherGO);

	/// <summary>
	/// Callback for trgger collision
	/// </summary>
	/// <param name="thisGO"></param>
	/// <param name="otherGO"></param>
	static void gameObjectTriggered(GameObject* thisGO, GameObject* otherGO);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~ColliderComponent();

	/// <summary>
	/// Sets the collider for collisions
	/// </summary>
	void setCollider();

	/// <summary>
	/// Sets the collider as a trigger
	/// </summary>
	void setTrigger();

	/// <summary>
	/// Sets the position of the transform to a specified one
	/// </summary>
	void setPosition(Vector3 pos);

	/// <summary>
	/// Sets the rotation of the transform to a specified one
	/// </summary>
	void setRotation(Vector3 rot);

protected:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="id">Component ID</param>
	ColliderComponent(int id);

	void onEnable() override;

	void onDisable() override;

	Collider* _collider;
};

#endif // !COLLIDERCOMPONENT_H
//////////////////////////////////////////////////////

#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

class BoxColliderComponent : public ColliderComponent {
public:


	/// <summary>
	/// Contructor of the class
	/// </summary>
	BoxColliderComponent();

	void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Changes box size
	/// </summary>
	/// <param name="x">New width</param>
	/// <param name="y">New height</param>
	/// <param name="z">New depth</param>
	void setScale(float width, float heigh, float depth);
};

#endif

/////////////////////////////////////////////////////////


#ifndef SPHERECOLLIDERCOMPONENT_H
#define SPHERECOLLIDERCOMPONENT_H

class SphereColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	SphereColliderComponent();

	void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Changes sphere radius
	/// </summary>
	/// <param name="r">New new radius</param>
	void setScale(float radius);
};



#endif

////////////////////////////////////////////////////

#ifndef CAPSULECOLLIDERCOMPONENT_H
#define CAPSULECOLLIDERCOMPONENT_H

class CapsuleColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	CapsuleColliderComponent();

	void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Changes capsule's dimensions
	/// </summary>
	/// <param name="r">New radius</param>
	/// <param name="l">New length</param>
	void setScale(float radius, float length);
};


#endif
