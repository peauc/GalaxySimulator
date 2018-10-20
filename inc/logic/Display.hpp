#ifndef MULTICOREGALAXY_DISPLAY_HPP
#define MULTICOREGALAXY_DISPLAY_HPP
#include "Quadrant.hpp"
#include "Map.hpp"

class Display {
public:
	Display(int size, std::shared_ptr<Quadrant> &Quandrant,  std::list<std::shared_ptr<Star>> &star);
	void init(int arc, char **argv);
	static void render();
	static void drawQuadrants();
	static void drawQuadrantsRec(Quadrant *quadrant);
	
private:
	int size;
	std::shared_ptr<Quadrant> Quadrant;
	static void drawPoints(const std::list<std::shared_ptr<Star>> &vector);
};

#endif //MULTICOREGALAXY_DISPLAY_HPP
