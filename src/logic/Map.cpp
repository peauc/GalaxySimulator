#include <ctime>
#include <logic/Map.hpp>
#include "logic/Map.hpp"

Map::Map()
{
	this->quadrantRoot = std::make_shared<Quadrant>(LENGTH);
	this->generateStarMap();
	for(auto &it : this->starList) {
		this->quadrantRoot->insertToNode(it);
	}
}

void Map::generateStarMap()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	auto center_star = std::make_shared<Star>(LENGTH / 2, LENGTH / 2, 100000);
	this->starList.emplace_back(center_star);
	for(int i = 0; i < 5; ++i) {
		auto star = std::make_shared<Star>(
			250 + std::rand() % 500,
			250 + std::rand() % 500,
			10);
		this->starList.emplace_back(star);
	}
	
}


std::ostream &operator <<(std::ostream &os, const Map &map)
{
	auto j = 0;
	for(auto i = map.starList.begin(); i != map.starList.end(); i++, j++) {
		auto pair = (*i)->getPosition();
		os << std::to_string(pair.first) +" " +
		std::to_string(pair.second) + " with mass " +
		std::to_string((*i)->getWeight()) +
		'\n';
	}
	return (os << std::endl);
}

std::shared_ptr<Quadrant> &Map::getQuadrantRoot()
{
	return quadrantRoot;
}
std::list<std::shared_ptr<Star>> &Map::getStarList()
{
	return starList;
}
