#ifndef MULTICOREGALAXY_DISPLAY_HPP
#define MULTICOREGALAXY_DISPLAY_HPP
#include "Quadrant.hpp"
#include "Map.hpp"

class Display {
public:
	Display(int size, std::shared_ptr<Quadrant> Quandrant);
	void init(int arc, char **argv);
	static void render();
	static void drawQuadrants();
	static void drawQuadrantsRec(Quadrant *quadrant);
	
private:
	int size;
	std::shared_ptr<Quadrant> Quadrant;
	static void drawPoints(const std::vector<Star> &vector);
};

#endif //MULTICOREGALAXY_DISPLAY_HPP
