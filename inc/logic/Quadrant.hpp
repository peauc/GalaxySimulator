//
// Created by Clément Péau on 2018-09-25.
//

#ifndef MULTICOREGALAXY_QUADRANT_HPP
#define MULTICOREGALAXY_QUADRANT_HPP
#include <vector>
#include "Star.hpp"

enum QuadrantPosition {
	NorthWest = 0,
	NorthEast = 1,
	SouthWest = 2,
	SouthEast = 3,
	None = -1
};

#define THETA 0.5
#define G 0.1
class Quadrant
{
public:
	//Gravitational constant
	//SubQuad Constructor
	Quadrant(double x, double y, double length, QuadrantPosition &position);
	//RootQuad Constructor
	Quadrant(double length);
	
	QuadrantPosition getPosition(const Star &star) const;
	double getLength() const;
	const std::vector<Star> &getContainedStarList() const;
	void insertToNode(Star &star);
	double getX() const;
	double getY() const;
	std::pair<double,double> computeTreeForce(const Star &star) const;
	std::pair<double, double> computeAcceleration(const Star &star1, const Star &star2) const;
	void computeMassOfQuadrant();
	double getCenterMassX() const;
	double getCenterMassY() const;
	double getMass() const;
	std::vector<Star> &getRawStarList();
private:
	unsigned long getNumberOfStarsContained() const;
	double length;
	double x;
	double y;
	double centerMassX;
	double centerMassY;
	double mass;
	
	std::vector<std::shared_ptr<Quadrant>>	quadrantList;
public:
	const std::vector<std::shared_ptr<Quadrant>> &getQuadrantList() const;
private:
	std::vector<Star>	starList;
	std::shared_ptr<Quadrant> getOrCreateSubQuadrant(Star &star);
	void addToStarList(Star &star);
};
#endif //MULTICOREGALAXY_QUADRANT_HPP
