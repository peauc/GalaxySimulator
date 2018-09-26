#ifndef MULTICOREGALAXY_DISPLAY_HPP
#define MULTICOREGALAXY_DISPLAY_HPP
#include "Quadrant.hpp"

class Display {
public:
	Display(int size, const Quadrant  &quadrant);
	void init(int arc, char **argv);
	static void render();
private:
	int size;
	std::shared_ptr<Quadrant> Quadrant;
};

#endif //MULTICOREGALAXY_DISPLAY_HPP
