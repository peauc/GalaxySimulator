#ifndef MULTICOREGALAXY_QUADRANT_HPP
#define MULTICOREGALAXY_QUADRANT_HPP
#include <vector>
#include <memory>
#include <tbb/task_group.h>
#include <OpenCL/cl.hpp>
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
		QuadrantContainer();
		QuadrantContainer(Quadrant &parent);
		QuadrantContainer(const QuadrantContainer &quadrant);
		~QuadrantContainer();
		QuadrantContainer &operator=(const QuadrantContainer &quad);
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
		const std::vector<std::shared_ptr<Quadrant>> &
		get_quadrantList() const;
		std::vector<std::shared_ptr<Quadrant>> getQuadrantList();
	private:
		class Quadrant	&_containerQuadrant;
		std::vector<std::shared_ptr<class Quadrant>> _quadrantList;
	};


public:
	Quadrant();
	Quadrant(double x, double y, double size, Quadrant *parent);
	Quadrant(const Quadrant &quad);
	Quadrant(Quadrant *quad);
	Quadrant &operator=(const Quadrant &quad);
	~Quadrant() = default;
	Quadrant(class Quadrant *quadrant, QuadrantContainer::QuadrantPosition &pos);
	void simulationLoop(tbb::task_group &gr, std::vector<std::shared_ptr<Star>> star, Quadrant &rc);
	void addToStarList(std::shared_ptr<Star> &star);
	void computeAccelerationForQuadrant(Star *pStar, unsigned long i, cl::Program *program, cl::Context *context, cl::Device *device, cl::CommandQueue &queue, cl::Buffer &d_array);
	void addToStarList(std::vector<std::shared_ptr<Star>> vec);
	void balance();
	void computeMassOfQuadrant();
	std::pair<double, double> computeAcceleration(std::shared_ptr<Star> star1, std::shared_ptr<Star> star2) const;
	const QuadrantContainer &get_links() const;
	 QuadrantContainer &getLinks();
	QuadrantContainer::QuadrantPosition getPosition(Star &star) const;
	unsigned int depth;
private:
	std::vector<std::shared_ptr<Star>> _starList;
	class QuadrantContainer _links;
	class Quadrant *parent;
	
	bool isLeaf();
	bool isNotContained(std::shared_ptr<Star> &shared_ptr);
	void insertToParentNodeRec(std::shared_ptr<Star> &shared_ptr);
	void verifyUselessQuadrant();
};

std::pair<double, double> computeTreeForce(Quadrant &quad, std::shared_ptr<Star> &star, double softener, double theta, double g);

#endif
