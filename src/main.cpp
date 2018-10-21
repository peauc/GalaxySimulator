
#include <iostream>
#include <vector>
#include "logic/RootQuadrant.hpp"
#include "logic/Star.hpp"


int main(int ac, char **av) {
	std::cout << "Start of the program" << '\n';
	std::srand(static_cast<unsigned int>(std::time(0)));
	std::vector<std::shared_ptr<Star>> vec;

	auto center_star = std::make_shared<Star>(1000 / 2, 1000 / 2, 100000);
	vec.emplace_back(center_star);
	for(int i = 0; i < 5 ; ++i) {
		vec.emplace_back(std::make_shared<Star>(
			250 + std::rand() % 500,
			250 + std::rand() % 500,
			10));
	}
	auto rq = RootQuadrant(1000);
	rq.getRootQuadrant().addToStarList(vec);
	rq.getRootQuadrant().balance();
	std::cout << "End of the program" << std::endl;
	return (0);
}
