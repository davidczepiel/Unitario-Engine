#include "Animator.h"
#include "GraphicsEngine.h"
#include "Exceptions.h"

#pragma warning(push, 0)
#include "OgreAnimationState.h"
#include "OgreEntity.h"
#include <OgreSceneManager.h>
#pragma warning(pop)

Animator::Animator(const std::string& entityNode, int entity) : _entity(nullptr), _animation(nullptr), _animate(true)
{
	try {
		_entity = static_cast<Ogre::Entity*>(GraphicsEngine::getInstance()->getSceneManager()->getSceneNode(entityNode)->getAttachedObject(entity));
	}
	catch (...) {
		throw AnimatorException("Animator couldn't get entity of " + entityNode);
	}
}

Animator::~Animator()
{
}

void Animator::update(float timeSinceLastFrame)
{
	if (_animate && _animation != nullptr && _animation->getEnabled() && !_animation->hasEnded()) {
		_animation->addTime(timeSinceLastFrame);
	}
}

void Animator::changeAnimation(const std::string& animationName, bool loop)
{
	if (_animation != nullptr) {
		_animation->setEnabled(false);
		_animation->setTimePosition(0);
	}

	_animation = _entity->getAnimationState(animationName);

	if (_animation == nullptr) {
		throw AnimatorException("Couldn't load " + animationName + " animation");
	}

	_animation->setEnabled(true);
	_animation->setLoop(loop);
}

void Animator::stopAnimation()
{
	_animate = false;
}

void Animator::continueAnimation()
{
	_animate = true;
}

void Animator::restartAnimation(bool loop)
{
	_animation->setEnabled(true);
	_animation->setLoop(loop);
	_animation->setTimePosition(0);

	_animate = true;
}
