#include <ctime>
#include "logic/Map.hpp"

Map::Map()
{
	this->generateStarMap();
}

void Map::generateStarMap()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	this->starList.emplace_back(Star(WITDH / 2, HEIGHT / 2, 100000));
	for(int i = 0; i < 1000; ++i) {
		this->starList.emplace_back(Star(
			std::rand() % 500,
			std::rand() % 500,
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

const Quadrant &Map::getQuadrantRoot() const
{
	return quadrantRoot;
}
