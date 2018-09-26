
#include <logic/Quadrant.hpp>
#include "logic/Quadrant.hpp"

double Quadrant::getLength() const
{
	return length;
}
void Quadrant::setLength(double length)
{
	Quadrant::length = length;
}
const std::__1::vector <Quadrant> &Quadrant::getContainedStarList() const
{
	return quadrantList;
}
void Quadrant::setStarList(const std::__1::vector <Quadrant> &starList)
{
	Quadrant::quadrantList = starList;
}
unsigned long Quadrant::getNumberOfStarsContained()
{
	return (this->quadrantList.size());
}
