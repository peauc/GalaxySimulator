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
	if (this->_quadrantList.at(pos) == nullptr) {
		this->_quadrantList.at(pos) = std::make_shared<Quadrant>(&_containerQuadrant, pos);
	}
}
std::shared_ptr<class Quadrant> Quadrant::QuadrantContainer::getOrCreateQuadrantAtPosition(Quadrant::QuadrantContainer::QuadrantPosition &pos)
{
	auto quadrant = this->getQuadrantAtPosition(pos);
	if (quadrant == nullptr)
		this->createQuadrantAtPosition(pos);
	return this->getQuadrantAtPosition(pos);
}
bool Quadrant::QuadrantContainer::isLeaf()
{
	for (auto &i: _quadrantList) {
		if (i != nullptr)
			return false;
	}
	return true;
}

void Quadrant::QuadrantContainer::balance()
{
	for (auto &item: _quadrantList) {
		if (item)
			item->balance();
	}
}

void Quadrant::QuadrantContainer::insertToNode(std::shared_ptr<Star> &item)
{
	auto pos = _containerQuadrant.getPosition(*item);
	auto quad = this->getOrCreateQuadrantAtPosition(pos);
	quad->addToStarList(item);
}

void Quadrant::QuadrantContainer::insertToNode(std::vector<std::shared_ptr<Star>> &starList)
{

	for (auto &item: starList) {
		this->insertToNode(item);
	}
}
const std::vector<std::shared_ptr<Quadrant>> &
Quadrant::QuadrantContainer::get_quadrantList() const
{
	return _quadrantList;
}

bool Quadrant::QuadrantContainer::isUseless()
{
	//If a quadrant is the leaf, he has things in his starlist so ret will be false.
	//Else we will look into each quadrant recursively if he has a star inside
	bool ret = this->_containerQuadrant._starList.empty();
	if (!this->isLeaf()) {
		for (auto &it: this->_quadrantList) {
			if (it && (!it->_links.isUseless() || !it->_starList.empty()))
				ret = false;
		}
	}
	return ret;
}
void Quadrant::QuadrantContainer::clearLinks()
{
	for(auto &i : this->_quadrantList) {
		i = nullptr;
	}
}
 std::vector<std::shared_ptr<Quadrant>> Quadrant::QuadrantContainer::getQuadrantList()
{
	return _quadrantList;
}

Quadrant::QuadrantContainer::QuadrantContainer(const QuadrantContainer &quadrant) : QuadrantContainer(quadrant._containerQuadrant)
{
	for(size_t i = 0; i < 4; i++) {
		this->_quadrantList[i] = quadrant._quadrantList[i];
	}
}
Quadrant::QuadrantContainer &
Quadrant::QuadrantContainer::operator =(const Quadrant::QuadrantContainer &quad)
{
	_containerQuadrant = quad._containerQuadrant;
	for(size_t i = 0; i < 4; i++) {
		this->_quadrantList[i] = quad._quadrantList[i];
	}
	return (*this);
}


