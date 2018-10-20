#ifndef MULTICOREGALAXY_QUADRANT_HPP
#define MULTICOREGALAXY_QUADRANT_HPP
#include <vector>
#include <memory>
#include "logic/Star.hpp"
#include "utils/SpacialInformations.hpp"

class Quadrant : public SpacialInformations {
	//Had to put the helper class inside the main class due to circular
	// inclusion problems, the code file is still
	// logic/QuadrantContainer.cpp
	class QuadrantContainer {
	public:
		enum QuadrantPosition {
			NorthWest = 0,
			NorthEast = 1,
			SouthWest = 2,
			SouthEast = 3,
			None = -1
		};
		QuadrantContainer(Quadrant &parent);
		~QuadrantContainer();
		void createQuadrantAtPosition(QuadrantPosition &pos);
		std::shared_ptr<class Quadrant> getQuadrantAtPosition(QuadrantPosition &pos);
		std::shared_ptr<class Quadrant> getOrCreateQuadrantAtPosition(QuadrantPosition &pos);
		QuadrantContainer(class QuadrantContainer &quadrantContainer) = default;
	private:
		class Quadrant	&_containerQuadrant;
		std::vector<std::shared_ptr<class Quadrant>> _quadrantList;
	};


public:
	~Quadrant() = default;
	Quadrant(class Quadrant &quadrant) = default;
	
	void insertToNode(std::shared_ptr<Star> star);
	QuadrantContainer::QuadrantPosition getPosition(Star &star) const;
	Quadrant(double x, double y, double size, Quadrant *parent);
private:
	std::vector<std::shared_ptr<Star>> _starList;
	class QuadrantContainer _links;
	class Quadrant *parent;
};

#endif
