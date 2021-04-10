#include "AnimatorComponent.h"
#include "MotorGrafico/Animator.h"
#include "Exceptions.h"
#include "Logger.h"

AnimatorComponent::AnimatorComponent(GameObject* gameObject): Component(6, gameObject), 
	_states(), _actualState(nullptr), _animator(new Animator())
{
	
}

AnimatorComponent::~AnimatorComponent()
{
	
}

void AnimatorComponent::lateUpdate()
{
	for(AnimatorComponent::Transition& transition : _actualState->transitions){
		if(transition.transition()) {
			_actualState = transition.nextState;
			//a lo mejor cambiar de estado en ogre con el animator
			break;
		}
	}
}

void AnimatorComponent::setInitialState(const std::string& name)
{
	AnimatorComponent::State* state = nullptr;

	for(AnimatorComponent::State currentstate : _states){
		if (currentstate.name == name) state = &currentstate;
		if (state != nullptr){
			_actualState = state;
			return;
		}
	}
	Logger::getInstance()->log(name + " state does not exist", Logger::Level::WARN);
}

void AnimatorComponent::createState(const std::string& name)
{
	bool foundState = false;
	for (const AnimatorComponent::State& state : _states) {
		if (state.name == name) {
			foundState = true;			
			break;
		}
	}
	if(!foundState) _states.push_back({ name, std::list<AnimatorComponent::Transition>() });
	throw AnimatorException(name + " already exists");
}

void AnimatorComponent::addTransition(const std::string& origin, TransitionFunction* function, const std::string& end)
{
	AnimatorComponent::State* originState = nullptr, *endState = nullptr;

	for(AnimatorComponent::State state : _states){
		if (state.name == origin) originState = &state;
		else if (state.name == end) endState = &state;

		if (originState != nullptr && endState != nullptr)
			break;
	}

	if (originState == nullptr)	throw AnimatorException(origin + " doesn't exists");
	if (endState == nullptr)	throw AnimatorException(end + " doesn't exists");
	
	originState->transitions.push_back({function, endState});
}

