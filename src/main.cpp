
#include <logic/Map.hpp>
#include <iostream>
#include <logic/Display.hpp>

int main(int ac, char **av) {
	Map m;
	Display d(1000, m.getQuadrantRoot());
	
	d.init(ac, av);
	
	std::cout << m << std::endl;
	return (0);
}
