//
// Created by Clément Péau on 2018-10-20.
//

#ifndef MULTICOREGALAXY_IPOSITION_HPP
#define MULTICOREGALAXY_IPOSITION_HPP

class SpacialInformations {
public:
	~SpacialInformations() = default;
	
	
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getMass() const;
	void setMass(double mass);
	double getHeight() const;
	void setHeight(double height);
	double getWidth() const;
	void setWidth(double width);
	double getCmx() const;
	void setCmx(double _cmx);
	double getCmy() const;
	void setCmy(double _cmy);
private:
	double _cmx;
	double _cmy;
	double _height;
	double _width;
	double _x;
	double _y;
	double _mass;
protected:
	SpacialInformations() = default;
	SpacialInformations(SpacialInformations &spacialInformations);
};
#endif //MULTICOREGALAXY_IPOSITION_HPP
