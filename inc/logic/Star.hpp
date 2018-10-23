#ifndef MULTICOREGALAXY_STAR_HPP
#define MULTICOREGALAXY_STAR_HPP
#include <utils/SpacialInformations.hpp>

class Star : public SpacialInformations {
public:
	Star(double x, double y, double mass);
	~Star() = default;
	
	Star(const Star &star);
private:
};

#endif //MULTICOREGALAXY_STAR_HPP
