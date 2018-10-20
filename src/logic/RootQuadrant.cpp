//
// Created by Clément Péau on 20/10/2018.
//

#include <logic/RootQuadrant.hpp>
#include "logic/RootQuadrant.hpp"

Quadrant &RootQuadrant::getRootQuadrant()
{
	return _rootQuadrant;
}

RootQuadrant::RootQuadrant(double size) : _rootQuadrant(0, 0, size, nullptr)
{
}
