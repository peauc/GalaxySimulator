#include <ctime>
#include <logic/Map.hpp>
#include "logic/Map.hpp"

Map::Map()
{
	this->quadrantRoot = std::make_shared<Quadrant>(LENGTH);
	this->generateStarMap();
	for(auto it = this->starList.begin(); it != this->starList.end() ; it++) {
		this->quadrantRoot->insertToNode(*it);
	}
	auto i = 0;
}

void Map::generateStarMap()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	this->starList.emplace_back(Star(LENGTH / 2, LENGTH / 2, 100000));
	for(int i = 0; i < 1000; ++i) {
		this->starList.emplace_back(Star(
			250 + std::rand() % 500,
			250 + std::rand() % 500,
			10));
	}
	
}


std::ostream &operator <<(std::ostream &os, const Map &map)
{
	auto j = 0;
	for(auto i = map.starList.begin(); i != map.starList.end(); i++, j++) {
		auto pair = (*i).getPosition();
		os << std::to_string(pair.first) +" " +
		std::to_string(pair.second) + " with mass " +
		std::to_string((*i).getWeight()) +
		'\n';
	}
	return (os << std::endl);
}

const std::shared_ptr<Quadrant> &Map::getQuadrantRoot() const
{
	return quadrantRoot;
}
