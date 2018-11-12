//
// Created by Clément Péau on 20/10/2018.
//

#ifndef MULTICOREGALAXY_DISPLAY_HPP
#define MULTICOREGALAXY_DISPLAY_HPP
#include <logic/RootQuadrant.hpp>
#include <tbb/task_group.h>



class Display {
public:
	Display(int size, std::shared_ptr<RootQuadrant> &rq, std::vector<std::shared_ptr<Star>> &star);
	void init(int arc, char **argv, tbb::task_group &g, std::shared_ptr<RootQuadrant> &rq);
	static void render();
	static void drawQuadrants(std::shared_ptr<RootQuadrant> &rc);
	static void drawQuadrantsRec(Quadrant &rq);

private:
	int size;
	std::shared_ptr<class Quadrant> Quadrant;
	static void drawPoints(const std::vector<std::shared_ptr<class Star>> &vector);
};

#endif //MULTICOREGALAXY_DISPLAY_HPP
