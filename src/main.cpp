
#include <iostream>
#include <GLUT/glut.h>
#include "logic/Display.hpp"
#include "logic/Map.hpp"
#include "logic/Display.hpp"
#include "logic/Quadrant.hpp"

int main(int ac, char **av) {
	Map m;
	Display d(1000, m.getQuadrantRoot());
	d.init(ac, av);
	return (0);
}
