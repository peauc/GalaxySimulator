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

#define SOFTENER 0.1*0.1
#define THETA 0.5
#define G 0.1
class Quadrant
{
public:
	//SubQuad Constructor
	Quadrant(double x, double y, double length, QuadrantPosition &position, Quadrant *quadrant);
	//RootQuad Constructor
	Quadrant(double length);
	
	QuadrantPosition getPosition(Star &star) const;
	const std::vector<std::shared_ptr<Star>> &getContainedStarList() const;
	std::vector<std::shared_ptr<Star>> &getRawStarList();
	const std::vector<std::shared_ptr<Quadrant>> &getQuadrantList() const;
	
	void insertToParent(std::shared_ptr<Star> &star);
	void adjustQuadrant();
	void insertToNode(std::shared_ptr<Star> & star);
	void computeMassOfQuadrant();
	
	double getLength() const;
	double getX() const;
	double getY() const;
	double getCenterMassX() const;
	double getCenterMassY() const;
	double getMass() const;
	bool isContained(std::shared_ptr<Star> &star);
	
	std::pair<double,double> computeTreeForce(std::shared_ptr<Star> star) const;
	std::pair<double, double> computeAcceleration(std::shared_ptr<Star> star1, std::shared_ptr<Star> star2) const;

private:
	double length;
	double x;
	double y;
	double centerMassX;
	double centerMassY;
	double mass;
	Quadrant *parent;
	
	void addToStarList(std::shared_ptr<Star> &star);
	unsigned long getNumberOfStarsContained() const;
	
	std::vector<std::shared_ptr<Quadrant>>	quadrantList;
	std::vector<std::shared_ptr<Star>>	starList;
	std::shared_ptr<Quadrant> getOrCreateSubQuadrant(std::shared_ptr<Star> &star);
	bool isLeafNode();
};
#endif //MULTICOREGALAXY_QUADRANT_HPP
