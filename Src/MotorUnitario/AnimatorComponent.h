#pragma once
#ifndef ANIMATORCOMPONENT_H
#define ANIMATORCOMPONENT_H

#include "Component.h"

#include <string>
#include <list>

class Animator;

class AnimatorComponent: public Component
{
using TransitionFunction = bool();
public:
	struct Transition;
	struct State;
	struct State {
		std::string name;
		std::list<Transition> transitions;
	};
	struct Transition {
		TransitionFunction* transition;
		State* nextState;
	};

public:
	/// <summary>
	/// </summary>
	/// <param name="gameObject"></param>
	AnimatorComponent(GameObject* gameObject);
	~AnimatorComponent();

	/// <summary>
	/// Checks if a transition must be made, and changes the animation to that state
	/// </summary>
	void lateUpdate();

	/// <summary>
	/// Sets the initial state, searches for such state by name
	/// </summary>
	/// <param name="name">: Name of the state the user wants to set as initial</param>
	void setInitialState(const std::string& name);

	/// <summary>
	/// Creates a state 
	/// </summary>
	/// <param name="name">: name of state must be an animation</param>
	void createState(const std::string& name);

	/// <summary>
	/// Adds a transition in origin to another state in its list of transitions
	/// </summary>
	/// <param name="origin">: origin state from which the transition will be made</param>
	/// <param name="function">: must return a boolean. If it returns true, the transition will be made</param>
	/// <param name="end">: the next state from origin</param>
	void addTransition(const std::string& origin, TransitionFunction* function, const std::string& end);

private:
	std::list<State> _states;
	State* _actualState;

	Animator* _animator;

};

#endif ANIMATORCOMPONENT_H