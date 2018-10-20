//
// Created by Clément Péau on 2018-10-20.
//

#include <iostream>
#include <logic/Star.hpp>
#include "../../inc/logic/Star.hpp"

Star::Star(double x, double y, double mass)
{
	setY(y);
	setX(x);
	setMass(mass);
}

Star::~Star()
{
	std::cout << "A star died" << std::endl;
}

Star::Star(const Star &star)
{
	setX(star.getX());
	setY(star.getY());
	setMass(star.getMass());
}



