#pragma once
#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include "MotorUnitario/Component.h"
#include <string>

class TestComponent: public Component
{
public:
	/// <summary>
	/// Default constructor of the class
	/// </summary>
	TestComponent();

	/// <summary>
	/// Checks the mouse position with the button position and size and change the state of the button.
	/// </summary>
	virtual void update() override;
};



#endif TESTCOMPONENT_H