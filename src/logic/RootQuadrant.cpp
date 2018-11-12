//
// Created by Clément Péau on 20/10/2018.
//

#include <cuda_runtime_api.h>
#include <tbb/parallel_for.h>
#include <cmath>
#include <logic/RootQuadrant.hpp>
#include <iostream>
#include <logic/StarContainer.hpp>
#include <npp.h>
#include "logic/RootQuadrant.hpp"
#include "cuda/cuda.hpp"



Quadrant &RootQuadrant::getRootQuadrant()
{
	return _rootQuadrant;
}

RootQuadrant::RootQuadrant(double size, std::vector<std::shared_ptr<Star>> &vec) : _rootQuadrant(0, 0, size, nullptr), _starVector(vec)
{
}

void RootQuadrant::simulationLoop()
{
	this->computeLock.lock();
	_rootQuadrant.computeMassOfQuadrant();
	//calculate the accel
	SpacialInformations vec[STAR_NB + 1];
	SpacialInformations *d_vec;
	std::vector<Quadrant> quadrantHolder;
//
	quadrantHolder.emplace_back(&_rootQuadrant);
	for(auto i = 0; i < STAR_NB + 1; i++) {
		vec[i] = *_starVector[i];
	}
	auto d_vecSize = sizeof(SpacialInformations) * (STAR_NB + 1);
	cudaMalloc((void **)&d_vec, d_vecSize);
	cudaMemcpy(&d_vec, &vec, d_vecSize, cudaMemcpyHostToDevice);
	// Since we can't  use recursion ,we're calculating the results layer by layer
	int a = 0;
	while (!quadrantHolder.empty()) {
		//Malloc of the QuadranVector
		auto quadvecSize = sizeof(Quadrant) * quadrantHolder.size();
		Quadrant *d_quadVec = nullptr;
		Quadrant *quadVec = (Quadrant *)malloc(quadvecSize);
		for (int i = 0; i < quadrantHolder.size(); i++) {
			quadVec[i] = quadrantHolder[i];
		}
		auto i = cudaMalloc((void **) &d_quadVec, quadvecSize);
		if (i != cudaSuccess) { printf("Cuda Malloc failed\n"); }
		auto d = cudaMemcpy(d_quadVec, quadVec, quadvecSize, cudaMemcpyHostToDevice);
		if (d != cudaSuccess) { printf("Cuda Memcpy failed\n"); }

		//Malloc of the res Array
		size_t	resArraySize = (STAR_NB +1) * 2;
		float	resArray[resArraySize];
		float	*d_resArray;
		i = cudaMalloc((void **)&d_resArray, resArraySize * sizeof(float));
		if (i != cudaSuccess) { printf("Cuda Malloc failed\n"); }

		//Kernel call
		compute_accel_cuda(d_vec, d_quadVec, d_resArray, STAR_NB, quadrantHolder.size());
		cudaDeviceSynchronize();
		cudaMemcpy(&resArray, d_resArray, resArraySize * sizeof(float), cudaMemcpyDeviceToHost);
		for (auto it = 0; it < _starVector.size(); it++) {
			if (!std::isnan(resArray[i * 2]) || !std::isnan(resArray[i * 2 + 1])) {
				this->_starVector[it]->setAccx(this->_starVector[i]->getAccx() + resArray[i * 2]);
				this->_starVector[it]->setAccy(this->_starVector[i]->getAccy() + resArray[i * 2 + 1]);
			}
		}
		std::vector<Quadrant> tmp;
		for(auto &it: quadrantHolder) {
			for (auto &it2 : it.getLinks().getQuadrantList())
				if (it2) {
					tmp.emplace_back(Quadrant(it2.get()));
				}
		}
		quadrantHolder.clear();
		quadrantHolder.insert(quadrantHolder.end(), tmp.begin(), tmp.end());
		free(quadVec);
		cudaFree(d_resArray);
		cudaFree(d_quadVec);
	}
	cudaFree(d_vec);
	for(auto &it: this->_starVector) {
		auto acc = computeTreeForce(this->_rootQuadrant, it, SOFTENER, THETA, G);
		it->setAccx(it->getAccx() + acc.first);
		it->setAccy(it->getAccy() + acc.second);
	}
	for (auto &it: _starVector) {
		it->setX(it->getX() + it->getAccx());
		it->setY(it->getY() + it->getAccy());
	}
	_rootQuadrant.balance();
	this->computeLock.unlock();
}

//Function to call for processing
std::pair<double, double> computeTreeForce(Quadrant &quad, std::shared_ptr<Star> &star, double softener, double theta, double g)
{
	
	double r, k, d = 0;
	auto acc = std::make_pair<double, double>(0, 0);
	
	d = quad.getWidth();
	r = sqrt(pow(star->getX() - quad.getCmx(), 2) +
		 pow(star->getY() - quad.getCmy(), 2) +
		 softener);
	// If d/r <= theta we take the quadrant center of mass and mass instead of every bodies
	if (d / r <= theta) {
		k = quad.getMass() * g / (pow(r + 5, 3));
		acc.first = k * (quad.getCmx() - star->getX());
		acc.second = k * (quad.getCmy() - star->getY());
		if (std::isnan(acc.first) || std::isnan(acc.second))
			return (std::make_pair<double, double>(0, 0));
	}
	else {
		for(const auto &it : quad.get_links().get_quadrantList()) {
			if (it) {
				auto tmp = computeTreeForce(*it ,star, softener, theta, g);
				acc.first += tmp.first;
				acc.second += tmp.second;
				if (std::isnan(acc.first) || std::isnan(acc.second))
					return (std::make_pair<double, double>(0, 0));
			}
		}
	}
	return acc;
}
