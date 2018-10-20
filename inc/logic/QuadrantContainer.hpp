//
// Created by Clément Péau on 2018-10-20.
//

#ifndef MULTICOREGALAXY_QUADRANTCONTAINER_HPP
#define MULTICOREGALAXY_QUADRANTCONTAINER_HPP

#include "Quadrant.hpp"

class QuadrantContainer {
public:
	QuadrantContainer();
	~QuadrantContainer();
	
	QuadrantContainer(QuadrantContainer &quadrantContainer) = default;
};

#endif //MULTICOREGALAXY_QUADRANTCONTAINER_HPP
