#pragma once

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <string>

namespace Ogre {
	class AnimationState;
	class Entity;
};

class Animator
{
public:
	/// <summary>
	/// </summary>
	/// <param name="entityNode">: name of the ogreNode of the entity you want to animate</param>
	/// <param name="entity">: the index of the entity in entityNode. By default is 0</param>
	Animator(const std::string& entityNode, int entity = 0);
	~Animator();

	/// <summary>
	/// Called every tick to advance the animation timeSinceLastFrame
	/// <para>Only updates if animation has not been stopped</para>
	/// </summary>
	/// <param name="timeSinceLastFrame">: time since last frame</param>
	void update(float timeSinceLastFrame);

	/// <summary>
	/// Used to check if an animation is set
	/// </summary>
	/// <returns>true if there is an animation</returns>
	inline bool hasAnimation() const { return _animation != nullptr; }

	/// <summary>
	/// Changes the animation to animationName
	/// </summary>
	/// <param name="animationName"></param>
	/// <param name="loop">: by default is set to true</param>
	/// <exception cref="AnimatorException">Throws if animationName doesn't correspond to any animation</exception>
	void changeAnimation(const std::string& animationName, bool loop = true);

	/// <summary>
	/// stops updating the animation in update()
	/// </summary>
	void stopAnimation();

	/// <summary>
	/// Continues updating the animation in update()
	/// </summary>
	void continueAnimation();

	/// <summary>
	/// Starts updating the animation and resets the animation timer to 0
	/// </summary>
	/// <param name="loop"></param>
	void restartAnimation(bool loop = true);

private:
	Ogre::Entity* _entity;
	Ogre::AnimationState* _animation;

	bool _animate;
};

#endif //!ANIMATOR_H