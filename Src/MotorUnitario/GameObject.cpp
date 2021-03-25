#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : children(), components(), transform(nullptr), parent(nullptr), enable(true), persist(false)
{
	//transform = new Transform();
	//components->add(0, tranform);		???
}

void GameObject::start()
{
	for (Component* comp : components)
		if(comp->getEnable()) 
			comp->start();

	for (GameObject* go : children)
		if(go->getEnable()) 
			go->start();
}

void GameObject::update()
{
	for (Component* comp : components)
		if (comp->getEnable()) 
			comp->update();

	for (GameObject* go : children)
		if (go->getEnable()) 
			go->update();
}

void GameObject::fixedUpdate()
{
	for (Component* comp : components)
		if (comp->getEnable()) 
			comp->fixedUpdate();

	for (GameObject* go : children)
		if (go->getEnable()) 
			go->fixedUpdate();
}

void GameObject::lateUpdate()
{
	for (Component* comp : components)
		if (comp->getEnable()) 
			comp->fixedUpdate();

	for (GameObject* go : children)
		if (go->getEnable()) 
			go->lateUpdate();
}

void GameObject::addComponent(Component* component_)
{

}

void GameObject::removeComponent(Component* component_)
{

}

void GameObject::addChild(GameObject* gameObject_)
{
	gameObject_->setParent(this);
	children.push_back(gameObject_);
}
