#ifndef MULTICOREGALAXY_MAP_HPP
#define MULTICOREGALAXY_MAP_HPP

#include <vector>
#include <list>
#include <ostream>
#include "Star.hpp"
#include "Quadrant.hpp"

#define WITDH 1000
#define HEIGHT 1000

class Map{
public:
	Map();
	
	friend std::ostream &operator <<(std::ostream &os, const Map &map);
	void generateStarMap();
private:
	Quadrant 		quadrantRoot;
public:
	const Quadrant &getQuadrantRoot() const;
private:
	std::list<Star>		starList;

};

#endif //MULTICOREGALAXY_MAP_HPP
