//
// Created by Clément Péau on 2018-09-25.
//

#ifndef MULTICOREGALAXY_QUADRANT_HPP
#define MULTICOREGALAXY_QUADRANT_HPP
#include <vector>
#include "Star.hpp"

enum QuadrantPosition {
	None,
	North,
	East,
	South,
	West
};

class Quadrant
{
public:
private:
	unsigned long getNumberOfStarsContained();
	double length;
public:
	double getLength() const;
	void setLength(double length);
	const std::vector<Quadrant> &getContainedStarList() const;
	void setStarList(const std::vector<Quadrant> &starList);
private:
	std::vector<Quadrant>	quadrantList;
	std::vector<Star>	starList;
};
#endif //MULTICOREGALAXY_QUADRANT_HPP
