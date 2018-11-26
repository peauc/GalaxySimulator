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
	setWidth(0);
	setHeight(0);
	setAccx(0);
	setAccy(0);
	setCmy(0);
	setCmx(0);
	setMass(mass);
	this->depth = 0;
}

Star::Star(const Star &star)
{
	setX(star.getX());
	setY(star.getY());
	setMass(star.getMass());
}
Star::Star()
{
	this->depth = 0;
	setY(0);
	setX(0);
	setWidth(0);
	setHeight(0);
	setAccx(0);
	setAccy(0);
	setCmy(0);
	setCmx(0);
	setMass(0);
}



