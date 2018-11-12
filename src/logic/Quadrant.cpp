//
// Created by Clément Péau on 2018-10-20.
//

#include <cmath>
#include "logic/Quadrant.hpp"
#include "logic/RootQuadrant.hpp"
#include <tbb/task.h>
#include <tbb/task_group.h>
#include <tbb/parallel_for.h>

Quadrant::Quadrant(class Quadrant *quadrant, QuadrantContainer::QuadrantPosition &pos) : SpacialInformations(), _links(*this), parent(quadrant)
{
	this->setX(0);
	this->setY(0);
	this->setAccy(0);
	this->setAccx(0);
	this->setCmx(0);
	this->setMass(0);
	this->setCmy(0);
	this->setWidth(quadrant->getWidth() / 2);
	this->setHeight(quadrant->getWidth() / 2);
	if (pos == QuadrantContainer::QuadrantPosition::NorthEast || pos == QuadrantContainer::QuadrantPosition::NorthWest)
		this->setY(quadrant->getY());
	else
		this->setY(quadrant->getY() + quadrant->getWidth() / 2);
	if (pos == QuadrantContainer::QuadrantPosition::SouthEast || pos == QuadrantContainer::QuadrantPosition::NorthEast)
		this->setX( quadrant->getX() + quadrant->getWidth() / 2);
	else
		this->setX(quadrant->getX());
}

Quadrant::Quadrant() : _links(*this), SpacialInformations() {
}

Quadrant::Quadrant(double x, double y, double size, Quadrant *parent) : SpacialInformations(),
	_links(*this)
{
	this->setX(x);
	this->setY(y);
	this->setAccy(0);
	this->setAccx(0);
	this->setCmx(0);
	this->setCmy(0);
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

void Quadrant::insertToParentNodeRec(std::shared_ptr<Star> &shared_ptr)
{
	if (isNotContained(shared_ptr) && this->parent)
		this->parent->insertToParentNodeRec(shared_ptr);
	else
		this->_starList.emplace_back(shared_ptr);
}

void Quadrant::balance()
{
	for(auto i = 0; i < this->_starList.size(); i++) {
		if (this->isNotContained(this->_starList[i])) {
			if (this->parent) {
				this->parent->insertToParentNodeRec(this->_starList[i]);
				this->_starList.erase(
					this->_starList.begin() + i);
				--i;
				
			} // Out of the screen
			else {
				this->_starList.erase(this->_starList.begin() + i);
				--i;
			}
		}
	}
	if (this->getWidth() / 2 > 1) {
		if (this->_starList.size() > 1){
			this->_links.insertToNode(this->_starList);
			this->_starList.clear();
		}
	}
	if (!this->isLeaf()) {
		this->_links.balance();
		this->verifyUselessQuadrant();
	}
}

void Quadrant::verifyUselessQuadrant()
{
	if (this->_links.isUseless())
		this->_links.clearLinks();
}

bool Quadrant::isLeaf()
{
	return (this->_links.isLeaf());
}

void Quadrant::computeMassOfQuadrant()
{
	if (this->_starList.size() == 1) {
		auto star = this->_starList.front();
		this->setCmx(star->getX());
		this->setCmy(star->getY());
		this->setMass(star->getMass());
	} else {
		this->setMass(0);
		this->setCmy(0);
		this->setCmx(0);
		
		for(auto &it: this->_links.get_quadrantList()) {
			if (it) {
				it->computeMassOfQuadrant();
				this->setMass(it->getMass() + this->getMass());
				this->setCmx(this->getCmx() + (it->getCmx() * it->getMass()));
				this->setCmy(this->getCmy() + (it->getCmy() * it->getMass()));
			}
		}
		this->setCmx(this->getCmx() / this->getMass());
		this->setCmy(this->getCmy() / this->getMass());
	}
	
}

Quadrant::Quadrant(const Quadrant &quadrant) : SpacialInformations(),  _links(quadrant.get_links()) {
	this->_links = quadrant.get_links();
	this->setAccx(quadrant.getAccx());
	this->setAccy(quadrant.getAccy());
	this->setCmx(quadrant.getCmx());
	this->setCmy(quadrant.getCmy());
	this->setHeight(quadrant.getHeight());
	this->setWidth(quadrant.getWidth());
	this->setX(quadrant.getX());
	this->setY(quadrant.getY());
}

Quadrant::Quadrant(Quadrant *quadrant) : SpacialInformations(), _links(quadrant->get_links()){

	this->setAccx(quadrant->getAccx());
	this->setAccy(quadrant->getAccy());
	this->setCmx(quadrant->getCmx());
	this->setCmy(quadrant->getCmy());
	this->setHeight(quadrant->getHeight());
	this->setWidth(quadrant->getWidth());
	this->setX(quadrant->getX());
	this->setY(quadrant->getY());
	
}

Quadrant::QuadrantContainer &Quadrant::getLinks()
{
	return _links;
}

bool Quadrant::isNotContained(std::shared_ptr<Star> &star)
{
	return (star->getX() < this->getX() || star->getX() > this->getX() + this->getWidth() || star->getY() < this->getY() || star->getY() > this->getY() + this->getWidth());
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

const Quadrant::QuadrantContainer &Quadrant::get_links() const
{
	return _links;
}

Quadrant &Quadrant::operator =(const Quadrant &quadrant)
{
	this->setAccx(quadrant.getAccx());
	this->setAccy(quadrant.getAccy());
	this->setCmx(quadrant.getCmx());
	this->setCmy(quadrant.getCmy());
	this->setHeight(quadrant.getHeight());
	this->setWidth(quadrant.getWidth());
	this->setX(quadrant.getX());
	this->setY(quadrant.getY());
	
	return *this;
}
