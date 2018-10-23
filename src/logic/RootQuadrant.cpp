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

void RootQuadrant::simulationLoop(tbb::task_group &gr)
{
	gr.run([this]()
	       {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
		       while (true) {
			       computeLock.lock();
			       _rootQuadrant.computeMassOfQuadrant();
			       //calculate the accel
			       std::cout << this->_starVector.size() << std::endl;
			       tbb::parallel_for(
				       tbb::blocked_range<size_t>(0, this->_starVector.size()), [this](const tbb::blocked_range<size_t> &it)
				       {
					       for(size_t i = it.begin(); i < it.end(); i++) {
						       auto acc = computeTreeForce(this->getRootQuadrant(), this->_starVector[i], SOFTENER, THETA, G);
						       this->_starVector[i]->setAccx(this->_starVector[i]->getAccx() + acc.first);
						       this->_starVector[i]->setAccy(this->_starVector[i]->getAccy() + acc.second);
					       }
				       });
			       //apply the accel
			       tbb::parallel_for(tbb::blocked_range<size_t>(0, this->_starVector.size()), [this](const tbb::blocked_range<size_t> &it)
			       {
				       for(size_t i = it.begin(); i < it.end(); i++) {
					       this->_starVector[i]->setX(this->_starVector[i]->getX() + this->_starVector[i]->getAccx());
					       this->_starVector[i]->setY(this->_starVector[i]->getY() + this->_starVector[i]->getAccy());
				       }
			       });
			       _rootQuadrant.balance();
			       displayLock.unlock();
		       }
#pragma clang diagnostic pop
	       });
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
		if (isnan(acc.first) || isnan(acc.second))
			return (std::make_pair<double, double>(0, 0));
	} else {
		for(const auto &it : quad.get_links().get_quadrantList()) {
			if (it) {
				auto tmp = computeTreeForce(*it ,star, softener, theta, g);
				acc.first += tmp.first;
				acc.second += tmp.second;
				if (isnan(acc.first) ||
				    isnan(acc.second))
					return (std::make_pair<double, double>(
						0, 0));
			}
		}
	}
	return acc;
}
