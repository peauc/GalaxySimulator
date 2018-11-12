
#include <iostream>
#include <vector>
#include <display/Display.hpp>
#include <tbb/task_group.h>
#include <tbb/task_scheduler_init.h>
#include "logic/RootQuadrant.hpp"
#include "logic/Star.hpp"

int main(int ac, char **av) {
	std::cout << "Start of the main thread" << '\n';
	
	//Set the random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
	//Create a vector of shared_ptr<Star>, this allow us to fit the stars into the quadtree while still having a strong reference on them
	std::vector<std::shared_ptr<Star>> vec;
	vec.emplace_back(std::make_shared<Star>(500, 500, 70000));
	for(int i = 0; i < STAR_NB; ++i) {
		vec.emplace_back(std::make_shared<Star>(
			250 + std::rand() % 500,
			250 + std::rand() % 500,
			10000));
	}
	auto rq = std::make_shared<RootQuadrant>(1000, vec);
	rq->getRootQuadrant().addToStarList(vec);
	rq->getRootQuadrant().balance();
	tbb::task_group g;
	printf("Out of process\n");
	auto d = Display(1000, rq, vec);
	d.init(ac, av, g, rq);
	std::cout << "End of the main thread" << std::endl;
	return (0);
}
