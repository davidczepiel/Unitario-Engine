#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "ComponentsFactory.h"
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
#include "Transform.h"

class ComponentFactory
{
public:
	virtual Component* create() const = 0;
};

class FactoryAdder {
public: 
	FactoryAdder(ComponentFactory* factory, const char* name) {
		ComponentsFactory::getInstance()->add(name, factory);
	}
};

/// <summary>
/// This is a macro that defines a factoryComponent class
/// </summary>
/// <param name="cmp">The component that returns the class</param>
#define CMP_FACTORY(cmp)										\
class cmp##Factory : public ComponentFactory					\
{																\
public:															\
    virtual Component* create() const { return new cmp(); };	\
};																\

#endif

#ifndef TRANSFORMFACTORY_H
#define TRANSFORMFACTORY_H

CMP_FACTORY(Transform);

#endif // !TRANSFORMFACTORY_H


#ifndef IMAGERENDERFACTORY_H
#define IMAGERENDERFACTORY_H

CMP_FACTORY(ImageRenderComponent);

#endif // !IMAGERENDERFACTORY_H

#ifndef LIGHTCOMPONENTFACTORY_H
#define LIGHTCOMPONENTFACTORY_H

CMP_FACTORY(LightComponent);

#endif // !LIGHTCOMPONENTFACTORY_H

#ifndef RENDEROBJECTFACTORY_H
#define RENDEROBJECTFACTORY_H

CMP_FACTORY(RenderObjectComponent);

#endif // !RENDEROBJECTFACTORY_H

#ifndef LISTENERCOMPONENTFACTORY_H
#define LISTENERCOMPONENTFACTORY_H

CMP_FACTORY(ListenerComponent);

#endif // !LISTENERCOMPONENTFACTORY_H

#ifndef AUDIOSOURCECOMPONENTFACTORY_H
#define AUDIOSOURCECOMPONENTFACTORY_H

CMP_FACTORY(AudioSourceComponent);

#endif // !AUDIOSOURCECOMPONENTFACTORY_H

#ifndef RIGIDBODYCOMPONENTFACTORY_H
#define RIGIDBODYCOMPONENTFACTORY_H

CMP_FACTORY(RigidBodyComponent);

#endif // !RIGIDBODYCOMPONENTFACTORY_H

#ifndef BOXCOLLIDERCOMPONENTFACTORY_H
#define BOXCOLLIDERCOMPONENTFACTORY_H

CMP_FACTORY(BoxColliderComponent);

#endif // !BOXCOLLIDERCOMPONENTFACTORY_H

#ifndef SPHERECOLLIDERCOMPONENTFACTORY_H
#define SPHERECOLLIDERCOMPONENTFACTORY_H

CMP_FACTORY(SphereColliderComponent);

#endif // !SPHERECOLLIDERCOMPONENTFACTORY_H

#ifndef CAPSULECOLLIDERCOMPONENTFACTORY_H
#define CAPSULECOLLIDERCOMPONENTFACTORY_H

CMP_FACTORY(CapsuleColliderComponent);

#endif // !CAPSULECOLLIDERCOMPONENTFACTORY_H

#ifndef CAMERACOMPONENTFACTORY_H
#define CAMERACOMPONENTFACTORY_H

CMP_FACTORY(CameraComponent);

#endif // !COLLIDERCOMPONENTFACTORY_H

#ifndef ANIMATORCOMPONENTFACTORY_H
#define ANIMATORCOMPONENTFACTORY_H

CMP_FACTORY(AnimatorComponent);

#endif // !ANIMATORCOMPONENTFACTORY_H

#ifndef PARTICLESYSTEMCOMPONENTFACTORY_H
#define PARTICLESYSTEMCOMPONENTFACTORY_H

CMP_FACTORY(ParticleSystemComponent);

#endif // !PARTICLESYSTEMCOMPONENTFACTORY_H

#ifndef BUTTONCOMPONENTFACTORY_H
#define BUTTONCOMPONENTFACTORY_H

CMP_FACTORY(ButtonComponent);

#endif // !BUTTONCOMPONENTFACTORY_H

#ifndef OVERLAYCOMPONENTFACTORY_H
#define OVERLAYCOMPONENTFACTORY_H

CMP_FACTORY(OverlayComponent);

#endif // !OVERLAYCOMPONENTFACTORY_H