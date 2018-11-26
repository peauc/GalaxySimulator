#ifndef MULTICOREGALAXY_ROOTQUADRANT_HPP
#define MULTICOREGALAXY_ROOTQUADRANT_HPP
#include <mutex>
#include "Quadrant.hpp"
#include "OpenCL/cl.hpp"


class RootQuadrant{
public:
	cl::Program *program;
	cl::Context *context;
	cl::Device *defaultDevice;
	RootQuadrant(double size, std::vector<std::shared_ptr<Star>> &vec);
	~RootQuadrant() = default;
	void simulationLoop();
	std::mutex computeLock;
	
	RootQuadrant(RootQuadrant &rootQuadrant) = default;
	Quadrant &getQuadrant();
private:
	std::vector<std::shared_ptr<Star>> _starVector;
	Quadrant _rootQuadrant;
	void computeAcceleration();
	void applyAcceleration();
};

#endif //MULTICOREGALAXY_ROOTQUADRANT_HPP
