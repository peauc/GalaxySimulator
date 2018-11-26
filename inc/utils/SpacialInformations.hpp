//
// Created by Clément Péau on 2018-10-20.
//

#ifndef MULTICOREGALAXY_IPOSITION_HPP
#define MULTICOREGALAXY_IPOSITION_HPP

class SpacialInformations {
public:
	SpacialInformations();
	SpacialInformations(SpacialInformations &spacialInformations);
	SpacialInformations &operator=(const SpacialInformations &spacialInformations);
	~SpacialInformations() = default;
	
	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	float getMass() const;
	void setMass(float mass);
	float getHeight() const;
	void setHeight(float height);
	float getWidth() const;
	void setWidth(float width);
	float getCmx() const;
	void setCmx(float _cmx);
	float getCmy() const;
	void setCmy(float _cmy);
	float getAccx() const;
	void setAccx(float _accx);
	float getAccy() const;
	void setAccy(float _accy);

	float _cmx;
	float _cmy;
	float _height;
	float _width;
	float _accx;
	float _accy;
	float _x;
	float _y;
	float _mass;
};
#endif //MULTICOREGALAXY_IPOSITION_HPP
