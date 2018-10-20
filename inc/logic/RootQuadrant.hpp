#ifndef MULTICOREGALAXY_ROOTQUADRANT_HPP
#define MULTICOREGALAXY_ROOTQUADRANT_HPP

#include "Quadrant.hpp"

class RootQuadrant{
public:
	RootQuadrant(double size);
	~RootQuadrant() = default;
	
	RootQuadrant(RootQuadrant &rootQuadrant) = default;
	Quadrant &getRootQuadrant();
private:
	Quadrant _rootQuadrant;
};

#endif //MULTICOREGALAXY_ROOTQUADRANT_HPP
