//
// Created by Clément Péau on 20/10/2018.
//

#include <tbb/parallel_for.h>
#include <cmath>
#include <logic/RootQuadrant.hpp>
#include <iostream>
#include "logic/RootQuadrant.hpp"

Quadrant &RootQuadrant::getRootQuadrant()
{
	return _rootQuadrant;
}

RootQuadrant::RootQuadrant(double size, std::vector<std::shared_ptr<Star>> &vec) : _rootQuadrant(0, 0, size, nullptr), _starVector(vec)
{
}

void RootQuadrant::simulationLoop()
{
	_rootQuadrant.computeMassOfQuadrant();
	//calculate the accel
	
	for(auto &it: this->_starVector) {
		auto acc = computeTreeForce(this->getRootQuadrant(), it, SOFTENER, THETA, G);
		it->setAccx(it->getAccx() + acc.first);
		it->setAccy(it->getAccy() + acc.second);
	}
	for (auto &it: this->_starVector) {
		it->setX(it->getX() + it->getAccx());
		it->setY(it->getY() + it->getAccy());
	}
	
	_rootQuadrant.balance();
}

//Function to call for processing
std::pair<double, double> computeTreeForce(Quadrant &quad, std::shared_ptr<Star> &star, double softener, double theta, double g)
{
	
	double r, k, d;
	auto acc = std::make_pair<double, double>(0, 0);
	r = sqrt(pow(star->getX() - quad.getCmx(), 2) +
		 pow(star->getY() - quad.getCmy(), 2) +
		 softener);
	d = quad.getWidth();
	if (d / r <= theta) {
		k = quad.getMass() * g / (pow(r + 5, 3));
		acc.first = k * (quad.getCmx() - star->getX());
		acc.second = k * (quad.getCmy() - star->getY());
		if (std::isnan(acc.first) || std::isnan(acc.second))
			return (std::make_pair<double, double>(0, 0));
	} else {
		for(const auto &it : quad.get_links().get_quadrantList()) {
			if (it) {
				auto tmp = computeTreeForce(*it ,star, softener, theta, g);
				acc.first += tmp.first;
				acc.second += tmp.second;
				if (std::isnan(acc.first) ||
				    std::isnan(acc.second))
					return (std::make_pair<double, double>(
						0, 0));
			}
		}
	}
	return acc;
}
