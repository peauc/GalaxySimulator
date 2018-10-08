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
	
	void generateQuadrantTree();
	void generateStarMap();
	friend std::ostream &operator <<(std::ostream &os, const Map &map);
	const std::shared_ptr<Quadrant> &getQuadrantRoot() const;
	
private:
	std::shared_ptr<Quadrant> 	quadrantRoot;
public:
	const std::list<Star> &getStarList() const;
private:
	std::list<Star>		starList;

};

#endif //MULTICOREGALAXY_MAP_HPP
