//
// Created by Clément Péau on 2018-10-20.
//

#include "logic/Quadrant.hpp"

Quadrant::Quadrant(class Quadrant &quadrant, QuadrantContainer::QuadrantPosition &pos) : _links(*this)
{
	this->setWidth(quadrant.getWidth() / 2);
	this->setHeight(quadrant.getWidth() / 2);
	if (pos == QuadrantContainer::QuadrantPosition::NorthEast || pos == QuadrantContainer::QuadrantPosition::NorthWest)
		this->setY(quadrant.getY());
	else
		this->setY(quadrant.getY() + quadrant.getWidth() / 2);
	if (pos == QuadrantContainer::QuadrantPosition::SouthEast || pos == QuadrantContainer::QuadrantPosition::NorthEast)
		this->setX( quadrant.getX() + quadrant.getWidth() / 2);
	else
		this->setX(quadrant.getX());
}

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

void Quadrant::balance()
{
	if (this->getWidth() / 2 > 1) {
		if (this->_starList.size() != 1 && this->isLeaf()){
			this->_links.insertToNode(this->_starList);
			this->_starList.clear();
		}
	}
	if (!this->isLeaf()) {
		this->_links.balance();
	}
}
bool Quadrant::isLeaf()
{
	return (this->_links.isLeaf());
}

void Quadrant::addToStarList(std::vector<std::shared_ptr<Star>> vec)
{
	for (auto &it: vec)
		this->addToStarList(it);
}
void Quadrant::addToStarList(std::shared_ptr<Star> &star)
{
	this->_starList.emplace_back(std::move(star));
}
