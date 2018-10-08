
#include <logic/Quadrant.hpp>
#include <cmath>
#include "logic/Quadrant.hpp"

void Quadrant::insertToNode(Star &star)
{
	if (this->getNumberOfStarsContained() == 0 || this->length / 2 < 1) {
		this->addToStarList(star);
	}else if (this->getNumberOfStarsContained() > 1)
	{
		//Find the good quadrant and if it dosnt exist create it and
		// send the particule inside, otherwise, recursively call
		// this method
		auto subQuadrant = this->getOrCreateSubQuadrant(star);
		subQuadrant->insertToNode(star);
		this->addToStarList(star);
	}
	// If there is only one star contained in the quadrant we create
	// subquadrants and set the existing star to one
	else if (this->getNumberOfStarsContained() == 1) {
		auto existingStar = this->starList.front();
		auto quadrant = this->getOrCreateSubQuadrant(existingStar);
		quadrant->insertToNode(existingStar);
		
		quadrant = this->getOrCreateSubQuadrant(star);
		quadrant->insertToNode(star);
		this->addToStarList(star);
	}
	// If there is no star contained in this quadrant the star passed as
	// parameter is put in
	
}

//try to get the SubQuadrant if it does not exist it created it
std::shared_ptr<Quadrant> Quadrant::getOrCreateSubQuadrant(Star &star)
{
	auto position = this->getPosition(star);
	auto subQuadrant = this->quadrantList.at(position);
	if (subQuadrant == nullptr) {
		auto newQuadrant = std::make_shared<Quadrant>(this->getX(), this->getY(), this->getLength(), position);
		this->quadrantList[position] = newQuadrant;
		return newQuadrant;
	}
	return subQuadrant;
}

QuadrantPosition Quadrant::getPosition(const Star &star) const
{
	auto relativeX = star.getX() - this->getX();
	auto relativeY = star.getY() - this->getY();
	auto halfQuadrantLength = this->length / 2;
	
	if (relativeX > halfQuadrantLength && relativeY <= halfQuadrantLength)
	{
		return NorthEast;
	} else if (relativeX <= halfQuadrantLength && relativeY <= halfQuadrantLength) {
		return NorthWest;
	} else if (relativeX <= halfQuadrantLength && relativeY > halfQuadrantLength) {
		return SouthWest;
	} else
		return SouthEast;
	
}


//Create an empty quadrant and initialize the quadrantList
Quadrant::Quadrant(double x, double y, double length, QuadrantPosition &position)
{
	this->length = length / 2;
	if (position == NorthEast || position == NorthWest)
		this->y = y;
	else
		this->y = y + length / 2;
	if (position == SouthEast || position == NorthEast)
		this->x = x + length / 2;
	else
		this-> x = x;
	this->quadrantList =
		{
			nullptr,
			nullptr,
			nullptr,
			nullptr,
		};
}

//create Root Quadrant
Quadrant::Quadrant(double length)
{
	this->x = 0;
	this->y = 0;
	this->length = length;
	this->quadrantList =
		{
			nullptr,
			nullptr,
			nullptr,
			nullptr,
		};
}

void Quadrant::computeMassOfQuadrant()
{
	if (this->getNumberOfStarsContained() == 1) {
		auto star = starList.front();
		this->centerMassX = star.getX();
		this->centerMassY = star.getY();
		this->mass = star.getWeight();
	} else {
		this->mass = 0;
		this->centerMassY = 0;
		this->centerMassX = 0;
		
		double ret = 0;
		for(auto it = this->getQuadrantList().begin(); it < this->getQuadrantList().end(); it++) {
			(*it)->computeMassOfQuadrant();
			this->mass += (*it)->getMass();
			this->centerMassX += (*it)->getCenterMassX() * (*it)->getMass();
			this->centerMassY += (*it)->getCenterMassY() * (*it)->getMass();
		}
		this->centerMassY /= this->getMass();
		this->centerMassX /= this->getMass();
	}
	
}

std::pair<double, double> Quadrant::computeTreeForce(const Star &star) const
{
	double r,k,d;
	auto acc = std::make_pair<double,double>(0, 0);
	
	if (this->getNumberOfStarsContained() == 1) {
		acc = this->computeAcceleration(star, this->getContainedStarList().front());
		
	} else {
		r = sqrt((star.getX() - this->getCenterMassX()) * (star.getX() - this->getCenterMassX()) +
			(star.getY() - this->getCenterMassY()) * (star.getY() - this->getCenterMassY()));
		d = this->getLength();
		if (d/r <= THETA) {
			k = this->getMass() * G / (r*r*r);
			acc.first =k * (this->centerMassX - star.getX());
			acc.second = k * (this->centerMassY - star.getY());
		} else {
			for(auto it = this->getQuadrantList().begin(); it != this->getQuadrantList().end() ; it++) {
				if (*it) {
					auto tmp = (*it)->computeTreeForce(star);
					acc.first += tmp.first;
					acc.second += tmp.second;
				}
			}
		}
	}
	
	return acc;
}

std::pair<double, double> Quadrant::computeAcceleration(const Star &star1, const Star &star2) const
{
	auto ret = std::make_pair<double, double>(0, 0);
	
	if ((&star1 == &star2) || (star1.getY() == star2.getY() && star1.getX() == star2.getX()))
		return ret;
	double r = sqrt((star1.getX() - star2.getX()) * (star1.getX() - star2.getX()) + (star1.getY() - star2.getY()) * (star1.getY() - star2.getY()));
	double k = G * star2.getWeight() / (r*r*r);
	ret.first = k * (star2.getX() - star1.getX());
	ret.second = k * (star2.getY() - star1.getY());
	return (ret);
}

double Quadrant::getCenterMassX() const
{
	return this->centerMassX;
}
double Quadrant::getCenterMassY() const
{
	return centerMassY;
}
double Quadrant::getMass() const
{
	return mass;
}

const std::vector<Star> &Quadrant::getContainedStarList() const
{
	return this->starList;
}

const std::vector<std::shared_ptr<Quadrant>> &Quadrant::getQuadrantList() const
{
	return this->quadrantList;
}

double Quadrant::getX() const
{
	return x;
}
double Quadrant::getY() const
{
	return y;
}
void Quadrant::addToStarList(Star &star)
{
	this->starList.emplace_back(star);
}

double Quadrant::getLength() const
{
	return length;
}

unsigned long Quadrant::getNumberOfStarsContained() const
{
	return (this->starList.size());
}
std::vector<Star> &Quadrant::getRawStarList()
{
	return (this->starList);
}
