//
// Created by Clément Péau on 20/10/2018.
//

#include <tbb/parallel_for.h>
#include <cmath>
#include <logic/RootQuadrant.hpp>
#include <iostream>
#include "logic/RootQuadrant.hpp"


Quadrant &RootQuadrant::getQuadrant()
{
	return _rootQuadrant;
}

RootQuadrant::RootQuadrant(double size, std::vector<std::shared_ptr<Star>> &vec) : _rootQuadrant(0, 0, size, nullptr), _starVector(vec)
{
}

void RootQuadrant::simulationLoop()
{
	_rootQuadrant.computeMassOfQuadrant();

	this->computeLock.lock();
	this->computeAcceleration();
	this->applyAcceleration();
	this->_rootQuadrant.balance();
	this->computeLock.unlock();
}

void RootQuadrant::computeAcceleration()
{
	Star *starArray = (Star *)malloc(sizeof(Star) * this->_starVector.size());
	for (auto i = 0; i < this->_starVector.size(); i++) {
		starArray[i] = *this->_starVector[i].get();
	}
	cl::Buffer d_starArray(*this->context, CL_MEM_READ_WRITE, sizeof(Star) * this->_starVector.size());
	cl::CommandQueue queue(*this->context, *this->defaultDevice);

	queue.enqueueWriteBuffer(d_starArray, CL_TRUE, 0, sizeof(Star) * this->_starVector.size(), starArray);
	
	this->getQuadrant().computeAccelerationForQuadrant(starArray, this->_starVector.size(), this->program, this->context, this->defaultDevice, queue, d_starArray);
	queue.finish();
	queue.flush();
	queue.enqueueReadBuffer(d_starArray, CL_TRUE, 0, sizeof(Star) * this->_starVector.size(), starArray);

	for (auto i = 0; i < this->_starVector.size(); i++) {
		this->_starVector[i]->setAccx(starArray[i].getAccx());
		this->_starVector[i]->setAccy(starArray[i].getAccy());
	}
}

void RootQuadrant::applyAcceleration()
{
	for (auto &it: _starVector) {
		it->setX(it->getX() + it->getAccx());
		it->setY(it->getY() + it->getAccy());
	}
}

