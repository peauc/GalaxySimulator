
#include <iostream>
#include <vector>
#include <display/Display.hpp>
#include <tbb/task_group.h>
#include "logic/RootQuadrant.hpp"
#include "logic/Star.hpp"


int main(int ac, char **av) {
	std::cout << "Start of the program" << '\n';
	std::srand(static_cast<unsigned int>(std::time(0)));
	std::vector<std::shared_ptr<Star>> vec;
	{
		auto center_star = std::make_shared<Star>(500, 500,
							  70000);
		vec.emplace_back(center_star);
	}
	for(int i = 0; i < 100; ++i) {
		vec.emplace_back(std::make_shared<Star>(
			250 + std::rand() % 500,
			250 + std::rand() % 500,
			10000));
	}
	auto rq = std::make_shared<RootQuadrant>(1000, vec);
	rq->getRootQuadrant().addToStarList(vec);
	rq->getRootQuadrant().balance();
	rq->computeLock.lock();
	rq->displayLock.lock();
	tbb::task_group g;
	rq->simulationLoop(g);
	auto d = Display(1000, rq, vec);
	d.init(ac, av, g);
	g.wait();
	std::cout << "End of the program" << std::endl;
	return (0);
}
