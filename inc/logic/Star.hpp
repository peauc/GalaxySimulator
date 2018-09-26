//
// Created by Clément Péau on 2018-09-25.
//

#ifndef MULTICOREGALAXY_NODE_HPP
#define MULTICOREGALAXY_NODE_HPP

class Star{
private:
//positions
double x,y;
double mass;

public:
	Star(double x, double y, int weight);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	std::pair<double, double> getPosition() const;
	double getWeight() const;
private:
	void setWeight(double weight);
};

#endif //MULTICOREGALAXY_NODE_HPP
