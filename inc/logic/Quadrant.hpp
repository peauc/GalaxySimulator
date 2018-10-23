#ifndef MULTICOREGALAXY_QUADRANT_HPP
#define MULTICOREGALAXY_QUADRANT_HPP
#include <vector>
#include <memory>
#include "logic/Star.hpp"
#include "utils/SpacialInformations.hpp"

#define THETA 0.5
#define G 0.0000066742
#define SOFTENER 1000

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
		void insertToNode(std::vector<std::shared_ptr<Star>> &starList);
		void insertToNode(std::shared_ptr<Star> &star);
		void balance();
		
		
		void createQuadrantAtPosition(QuadrantPosition &pos);
		std::shared_ptr<class Quadrant> getQuadrantAtPosition(QuadrantPosition &pos);
		std::shared_ptr<class Quadrant> getOrCreateQuadrantAtPosition(QuadrantPosition &pos);
		QuadrantContainer(class QuadrantContainer &quadrantContainer) = default;
		bool isLeaf();
		bool isUseless();
		void clearLinks();
	private:
	public:
		const std::vector<std::shared_ptr<Quadrant>> &
		get_quadrantList() const;
	private:
		class Quadrant	&_containerQuadrant;
		std::vector<std::shared_ptr<class Quadrant>> _quadrantList;
	};


public:
	Quadrant(double x, double y, double size, Quadrant *parent);
	~Quadrant() = default;
	Quadrant(class Quadrant *quadrant, QuadrantContainer::QuadrantPosition &pos);
	void addToStarList(std::shared_ptr<Star> &star);
	void addToStarList(std::vector<std::shared_ptr<Star>> vec);
	void balance();
	void computeMassOfQuadrant();
	std::pair<double, double> computeTreeForce(std::shared_ptr<Star> star) const;
	std::pair<double, double> computeAcceleration(std::shared_ptr<Star> star1, std::shared_ptr<Star> star2) const;
	const QuadrantContainer &get_links() const;
	QuadrantContainer::QuadrantPosition getPosition(Star &star) const;
private:
	std::vector<std::shared_ptr<Star>> _starList;
	class QuadrantContainer _links;
	class Quadrant *parent;
	
	bool isLeaf();
	bool isNotContained(std::shared_ptr<Star> &shared_ptr);
	void insertToParentNodeRec(std::shared_ptr<Star> &shared_ptr);
	void verifyUselessQuadrant();
};

#endif
