//
// Created by Clément Péau on 2018-10-20.
//

#include "logic/Quadrant.hpp"

Quadrant::Quadrant(double x, double y, double size, Quadrant *parent) :
	_links(*this)
{
	this->setX(x);
	this->setY(y);
	this->setHeight(size);
	this->setWidth(size);
	this->setMass(0);
	this->parent = parent;
}

void Quadrant::insertToNode(std::shared_ptr<Star> star)
{
	if (this->_starList.size() > 1) {
		auto existingStar = this->_starList.back();
		this->_starList.pop_back();
		this->getPosition(*star);
	}
}

Quadrant::QuadrantContainer::QuadrantPosition Quadrant::getPosition(Star &star) const
{
	auto relativeX = star.getX() - getX();
	auto relativeY = star.getY() - getY();
	auto halfQuadrantLength = getWidth() / 2;
	
	if (relativeX > halfQuadrantLength && relativeY <= halfQuadrantLength)
	{
		return QuadrantContainer::NorthEast;
	} else if (relativeX <= halfQuadrantLength && relativeY <= halfQuadrantLength) {
		return QuadrantContainer::NorthWest;
	} else if (relativeX <= halfQuadrantLength && relativeY > halfQuadrantLength) {
		return QuadrantContainer::SouthWest;
	} else
		return QuadrantContainer::SouthEast;
	
}

