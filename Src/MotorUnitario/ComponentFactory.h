#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"
#include "ImageRenderComponent.h"
#include "LightComponent.h"
#include "RenderObjectComponent.h"
#include "ListenerComponent.h"
#include "AudioSourceComponent.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "CameraComponent.h"
#include "AnimatorComponent.h"
#include "ParticleSystemComponent.h"
#include "ButtonComponent.h"
#include "OverlayComponent.h"

/// <summary>
/// This is a macro that defines a factoryComponent class
/// </summary>
/// <param name="factoryName">Class of the factory we want to create</param>
/// <param name="cmp">The component that returns the class</param>
#define CMP_FACTORY(factoryName,cmp)						\
class factoryName : public ComponentFactory					\
{                                                           \
public:                                                     \
	factoryName(){}											\
	virtual ~factoryName(){}								\
    virtual cmp* create() const { return new cmp(); };		\
};

class ComponentFactory
{
public:
	virtual Component* create() const = 0;

protected:
	ComponentFactory() {

	}
	virtual ~ComponentFactory() {}
};

#endif // !COMPONENTFACTORY_H

#ifndef IMAGERENDERFACTORY_H
#define IMAGERENDERFACTORY_H

CMP_FACTORY(ImageRenderComponentFactory, ImageRenderComponent);

#endif // !IMAGERENDERFACTORY_H

#ifndef LIGHTCOMPONENTFACTORY_H
#define LIGHTCOMPONENTFACTORY_H

CMP_FACTORY(LightComponentFactory, LightComponent);

#endif // !LIGHTCOMPONENTFACTORY_H

#ifndef RENDEROBJECTFACTORY_H
#define RENDEROBJECTFACTORY_H

CMP_FACTORY(RenderObjectComponentFactory, RenderObjectComponent);

#endif // !RENDEROBJECTFACTORY_H

#ifndef LISTENERCOMPONENTFACTORY_H
#define LISTENERCOMPONENTFACTORY_H

CMP_FACTORY(ListenerComponentFactory, ListenerComponent);

#endif // !LISTENERCOMPONENTFACTORY_H

#ifndef AUDIOSOURCECOMPONENTFACTORY_H
#define AUDIOSOURCECOMPONENTFACTORY_H

CMP_FACTORY(AudioSourceComponentFactory, AudioSourceComponent);

#endif // !AUDIOSOURCECOMPONENTFACTORY_H

#ifndef RIGIDBODYCOMPONENTFACTORY_H
#define RIGIDBODYCOMPONENTFACTORY_H

CMP_FACTORY(RigidBodyComponentFactory, RigidBodyComponent);

#endif // !RIGIDBODYCOMPONENTFACTORY_H

#ifndef BOXCOLLIDERCOMPONENTFACTORY_H
#define BOXCOLLIDERCOMPONENTFACTORY_H

CMP_FACTORY(BoxColliderComponentFactory, BoxColliderComponent);

#endif // !BOXCOLLIDERCOMPONENTFACTORY_H

#ifndef SPHERECOLLIDERCOMPONENTFACTORY_H
#define SPHERECOLLIDERCOMPONENTFACTORY_H

CMP_FACTORY(SphereColliderComponentFactory, SphereColliderComponent);

#endif // !SPHERECOLLIDERCOMPONENTFACTORY_H

#ifndef CAPSULECOLLIDERCOMPONENTFACTORY_H
#define CAPSULECOLLIDERCOMPONENTFACTORY_H

CMP_FACTORY(CapsuleColliderComponentFactory, CapsuleColliderComponent);

#endif // !CAPSULECOLLIDERCOMPONENTFACTORY_H

#ifndef CAMERACOMPONENTFACTORY_H
#define CAMERACOMPONENTFACTORY_H

CMP_FACTORY(CameraComponentFactory, CameraComponent);

#endif // !COLLIDERCOMPONENTFACTORY_H

#ifndef ANIMATORCOMPONENTFACTORY_H
#define ANIMATORCOMPONENTFACTORY_H

CMP_FACTORY(AnimatorComponentFactory, AnimatorComponent);

#endif // !ANIMATORCOMPONENTFACTORY_H

#ifndef PARTICLESYSTEMCOMPONENTFACTORY_H
#define PARTICLESYSTEMCOMPONENTFACTORY_H

CMP_FACTORY(ParticleSystemComponentFactory, ParticleSystemComponent);

#endif // !PARTICLESYSTEMCOMPONENTFACTORY_H

#ifndef BUTTONCOMPONENTFACTORY_H
#define BUTTONCOMPONENTFACTORY_H

CMP_FACTORY(ButtonComponentFactory, ButtonComponent);

#endif // !BUTTONCOMPONENTFACTORY_H

#ifndef OVERLAYCOMPONENTFACTORY_H
#define OVERLAYCOMPONENTFACTORY_H

CMP_FACTORY(OverlayComponentFactory, OverlayComponent);

#endif // !OVERLAYCOMPONENTFACTORY_H