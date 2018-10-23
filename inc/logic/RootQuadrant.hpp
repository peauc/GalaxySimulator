#ifndef MULTICOREGALAXY_ROOTQUADRANT_HPP
#define MULTICOREGALAXY_ROOTQUADRANT_HPP
#include <mutex>
#include "Quadrant.hpp"

class RootQuadrant{
public:
	RootQuadrant(double size, std::vector<std::shared_ptr<Star>> &vec);
	~RootQuadrant() = default;
	void simulationLoop(tbb::task_group &gr);
	std::mutex computeLock;
	std::mutex displayLock;
	
	RootQuadrant(RootQuadrant &rootQuadrant) = default;
	Quadrant &getRootQuadrant();
private:
	std::vector<std::shared_ptr<Star>> _starVector;
	Quadrant _rootQuadrant;
};

#endif //MULTICOREGALAXY_ROOTQUADRANT_HPP
