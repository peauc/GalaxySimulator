#ifndef MULTICOREGALAXY_QUADRANT_HPP
#define MULTICOREGALAXY_QUADRANT_HPP
#include <vector>
#include <memory>
#include <tbb/task_group.h>
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
		void insertToNode(std::vector<std::shared_ptr<class Star>> &starList);
		void insertToNode(std::shared_ptr<class Star> &star);
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
	void simulationLoop(tbb::task_group &gr, std::vector<std::shared_ptr<class Star>> star, Quadrant &rc);
	void addToStarList(std::shared_ptr<class Star> &star);
	void addToStarList(std::vector<std::shared_ptr<class Star>> vec);
	void balance();
	void computeMassOfQuadrant();
	std::pair<double, double> computeAcceleration(std::shared_ptr<class Star> star1, std::shared_ptr<class Star> star2) const;
	const QuadrantContainer &get_links() const;
	QuadrantContainer::QuadrantPosition getPosition(class Star &star) const;
private:
	std::vector<std::shared_ptr<class Star>> _starList;
	class QuadrantContainer _links;
	class Quadrant *parent;
	
	bool isLeaf();
	bool isNotContained(std::shared_ptr<class Star> &shared_ptr);
	void insertToParentNodeRec(std::shared_ptr<class Star> &shared_ptr);
	void verifyUselessQuadrant();
};

std::pair<double, double> computeTreeForce(Quadrant &quad, std::shared_ptr<class Star> &star, double softener, double theta, double g);

#endif
