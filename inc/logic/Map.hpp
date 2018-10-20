#ifndef MULTICOREGALAXY_MAP_HPP
#define MULTICOREGALAXY_MAP_HPP

#include <vector>
#include <list>
#include <ostream>
#include "Star.hpp"
#include "Quadrant.hpp"

#define LENGTH 1000

class Map{
public:
	Map();
	
	void generateStarMap();
	friend std::ostream &operator <<(std::ostream &os, const Map &map);
	std::shared_ptr<Quadrant> &getQuadrantRoot();
	std::list<std::shared_ptr<Star>> &getStarList();
private:
	std::shared_ptr<Quadrant>		quadrantRoot;
	std::list<std::shared_ptr<Star>>	starList;

};

#endif //MULTICOREGALAXY_MAP_HPP
