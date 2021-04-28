#pragma once

#ifndef COLLISIONBODY_H
#define COLLISIONBODY_H

class GameObject;

using ContactCallback = void(GameObject* thisGO, GameObject* otherGO);

class CollisionBody
{
public:
	virtual ~CollisionBody() {}
	inline virtual ContactCallback* getColliderCallback() const { return nullptr; }
	inline virtual GameObject* getGameObject() const { return nullptr; }

protected:
	CollisionBody() {}
};

#endif //!COLLISIONBODY_H