#pragma once
#ifndef COLOUR_H
#define COLOUR_H

struct Colour
{
	float red;
	float green;
	float blue;
	float alpha;

	Colour(): red(0), green(0), blue(0), alpha(1) {}
	Colour(float red, float green, float blue, float alpha = 1) : red(red), green(green), blue(blue), alpha(alpha) {}
}; 

#endif COLOUR_H