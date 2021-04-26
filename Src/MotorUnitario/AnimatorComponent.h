#pragma once
#ifndef ANIMATORCOMPONENT_H
#define ANIMATORCOMPONENT_H

#include "Component.h"

#include <string>
#include <list>

class Animator;

class AnimatorComponent: public Component
{
using TransitionFunction = bool(void*);
public:
	struct Transition;
	struct State;
	struct State {
		std::string name;
		bool loop;
		std::list<Transition> transitions;
	};
	struct Transition {
		TransitionFunction* transition;
		void* param;
		State* nextState;
	};

public:
	/// <summary>
	/// </summary>
	/// <param name="gameObject"></param>
	AnimatorComponent();

	~AnimatorComponent();
	
	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;

	/// <summary>
	/// Checks if a transition must be made, and changes the animation to that state
	/// </summary>
	void lateUpdate() override;

	/// <summary>
	/// Sets the initial state, searches for such state by name
	/// </summary>
	/// <param name="name">: Name of the state the user wants to set as initial</param>
	void setInitialState(const std::string& name);

	/// <summary>
	/// Creates a state 
	/// </summary>
	/// <param name="name">: name of state must be an animation</param>
	/// /// <exception cref="AnimatorException">throws if that state already exists</exception>
	void createState(const std::string& name, bool loop = true);

	/// <summary>
	/// Adds a transition in origin to another state in its list of transitions
	/// </summary>
	/// <param name="origin">: origin state from which the transition will be made</param>
	/// <param name="function">: must return a boolean. If it returns true, the transition will be made</param>
	/// <param name="end">: the next state from origin</param>
	/// <exception cref="AnimatorException">throws if origin or end States doesn't exist</exception>
	void addTransition(const std::string& origin, TransitionFunction* function, const std::string& end, void* functionParam = nullptr);

	/// <summary>
	/// Stops the animation from moving, but it can still change
	/// </summary>
	void stopAnimation();

	/// <summary>
	/// If it was stopped by stopAnimation(), makes the animation move again
	/// </summary>
	void continueAnimation();

	/// <summary>
	/// Restarts the animation to initialState and makes the animation move if it was stopped by stopAnimation()
	/// </summary>
	/// <exception cref="AnimatorException">throws initial state is not set</exception>
	void restartAnimation();

private:
	std::list<State> _states;
	State* _actualState, *_initialState;

	Animator* _animator;
};

ADD_COMPONENT(AnimatorComponent)

#endif ANIMATORCOMPONENT_H

