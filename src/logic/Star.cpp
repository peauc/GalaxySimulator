//
// Created by Clément Péau on 2018-09-25.
//

#include <utility>
#include <logic/Star.hpp>
#include <iostream>

Star::~Star()
{
	std::cout << "A star died" << std::endl;
}
double Star::getX() const
{
	return x;
}

void Star::setX(double x)
{
	Star::x = x;
}
double Star::getY() const
{
	return y;
}
void Star::setY(double y)
{
	Star::y = y;
}
double Star::getWeight() const
{
	return mass;
}
void Star::setWeight(double weight)
{
	Star::mass = weight;
}

Star::Star(double x, double y, int weight) : x(x), y(y), mass(weight)
{}

std::pair<double, double> Star::getPosition() const
{
	return std::make_pair<double, double>(this->getX(), this->getY());
}
