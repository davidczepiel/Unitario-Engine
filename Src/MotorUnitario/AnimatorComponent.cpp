#include "AnimatorComponent.h"
#include "MotorGrafico/Animator.h"
#include "Exceptions.h"
#include "Logger.h"

AnimatorComponent::AnimatorComponent(GameObject* gameObject): Component(6, gameObject), 
	_states(), _actualState(nullptr), _initialState(nullptr), _animator(new Animator())
{
	
}

AnimatorComponent::~AnimatorComponent()
{
	delete _animator; _animator = nullptr;
}

void AnimatorComponent::lateUpdate()
{
	//If initialState hasn't been set
	if (_actualState == nullptr) 
		return;

	for(const AnimatorComponent::Transition& transition : _actualState->transitions){
		if(transition.transition()) {
			_actualState = transition.nextState;
			_animator->changeAnimation(_actualState->name, _actualState->loop);
			break;
		}
	}

	//_animator->update(0.2f); Need time since last frame
}

void AnimatorComponent::setInitialState(const std::string& name)
{
	AnimatorComponent::State* state = nullptr;

	for(AnimatorComponent::State currentstate : _states){
		if (currentstate.name == name) state = &currentstate;
		if (state != nullptr){
			_actualState = state;
			_initialState = state;
			_animator->changeAnimation(_actualState->name, _actualState->loop);
			return;
		}
	}
	Logger::getInstance()->log(name + " state does not exist", Logger::Level::WARN);
}

void AnimatorComponent::createState(const std::string& name, bool loop)
{
	bool foundState = false;
	for (const AnimatorComponent::State& state : _states) {
		if (state.name == name) {
			foundState = true;			
			break;
		}
	}
	if(!foundState) _states.push_back({ name, loop, std::list<AnimatorComponent::Transition>() });
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

void AnimatorComponent::stopAnimation()
{
	if(_animator->hasAnimation())
		_animator->stopAnimation();
}

void AnimatorComponent::continueAnimation()
{
	if (_animator->hasAnimation())
		_animator->continueAnimation();
}

void AnimatorComponent::restartAnimation()
{
	_actualState = _initialState;
	if (_actualState != nullptr && _animator->hasAnimation()) {
		_animator->changeAnimation(_actualState->name, _actualState->loop);
		_animator->restartAnimation();
	}
	else throw AnimatorException("initial state is not set to any animation");
}

