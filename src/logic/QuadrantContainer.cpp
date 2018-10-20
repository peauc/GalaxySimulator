//
// Created by Clément Péau on 2018-10-20.
//

#include <logic/Quadrant.hpp>

Quadrant::QuadrantContainer::QuadrantContainer(Quadrant &parent) :
_containerQuadrant(parent),
_quadrantList({nullptr, nullptr, nullptr, nullptr})
{
}

Quadrant::QuadrantContainer::~QuadrantContainer()
{

}



std::shared_ptr<class Quadrant> Quadrant::QuadrantContainer::getQuadrantAtPosition(Quadrant::QuadrantContainer::QuadrantPosition &pos)
{
	return (this->_quadrantList.at(pos));
}
void Quadrant::QuadrantContainer::createQuadrantAtPosition(Quadrant::QuadrantContainer::QuadrantPosition &pos)
{
	if (this->_quadrantList.at(pos) == nullptr)
		this->_quadrantList.at(pos) = std::make_shared<Quadrant>(_containerQuadrant);
}
std::shared_ptr<class Quadrant> Quadrant::QuadrantContainer::getOrCreateQuadrantAtPosition(Quadrant::QuadrantContainer::QuadrantPosition &pos)
{
	auto quadrant = this->getQuadrantAtPosition(pos);
	if (quadrant == nullptr)
		this->createQuadrantAtPosition(pos);
	return this->getQuadrantAtPosition(pos);
}

