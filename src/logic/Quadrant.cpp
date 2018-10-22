//
// Created by Clément Péau on 2018-10-20.
//

#include <cmath>
#include "logic/Quadrant.hpp"

Quadrant::Quadrant(class Quadrant *quadrant, QuadrantContainer::QuadrantPosition &pos) : _links(*this), parent(quadrant)
{
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
			} // Out of the screen
			this->_starList.erase(this->_starList.begin() + i);
			--i;
		}
	}
	if (this->getWidth() / 2 > 1) {
		if (!this->_starList.empty()){
			this->_links.insertToNode(this->_starList);
			this->_starList.clear();
		}
	}
	if (!this->isLeaf()) {
		this->_links.balance();
		//this->verifyUselessQuadrant();
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
		setMass(star->getMass());
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

std::pair<double, double> Quadrant::computeTreeForce(std::shared_ptr<Star> star) const
{
	double r,k,d;
	auto acc = std::make_pair<double,double>(0, 0);
	
	r = sqrt((star->getX() - this->getCmx()) * (star->getX() - this->getCmx()) +
		 (star->getY() - this->getCmy()) * (star->getY() - this->getCmy()));
	d = this->getWidth();
	if (d/r <= THETA) {
		k = this->getMass() * G / (r*r*r);
		acc.first =k * (this->getCmx() - star->getX());
		acc.second = k * (this->getCmy() - star->getY());
	} else {
		for(const auto &it : this->get_links().get_quadrantList()) {
			if (it) {
				auto tmp = it->computeTreeForce(star);
				acc.first += tmp.first;
				acc.second += tmp.second;
			}
		}
	}
	
	
	return acc;
}

std::pair<double, double> Quadrant::computeAcceleration(std::shared_ptr<Star> star1, std::shared_ptr<Star> star2) const
{
	auto ret = std::make_pair<double, double>(0, 0);
	
	if ((&star1 == &star2) || (star1->getY() == star2->getY() && star1->getX() == star2->getX()))
		return ret;
	double r = sqrt((star1->getX() - star2->getX()) * (star1->getX() - star2->getX()) + (star1->getY() - star2->getY()) * (star1->getY() - star2->getY()));
	double k = G * star1->getMass() / (r*r*r);
	ret.first = k * (star2->getX() - star1->getX());
	ret.second = k * (star2->getY() - star1->getY());
	return (ret);
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
