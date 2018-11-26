//
// Created by Clément Péau on 2018-10-20.
//

#include <utils/SpacialInformations.hpp>
#import "utils/SpacialInformations.hpp"

SpacialInformations::SpacialInformations(SpacialInformations &spacialInformations)
{
	_x = spacialInformations.getX();
	_y = spacialInformations.getY();
	_mass = spacialInformations.getMass();
	_height = spacialInformations.getHeight();
	_width = spacialInformations.getWidth();
	_accx = spacialInformations.getAccx();
	_accy = spacialInformations.getAccy();
	_cmx = spacialInformations.getCmx();
	_cmy = spacialInformations.getCmy();
}

float SpacialInformations::getX() const
{
	return _x;
}
void SpacialInformations::setX(float x)
{
	SpacialInformations::_x = x;
}
float SpacialInformations::getY() const
{
	return _y;
}
void SpacialInformations::setY(float y)
{
	SpacialInformations::_y = y;
}
float SpacialInformations::getMass() const
{
	return _mass;
}
void SpacialInformations::setMass(float mass)
{
	SpacialInformations::_mass = mass;
}
float SpacialInformations::getHeight() const
{
	return _height;
}
void SpacialInformations::setHeight(float height)
{
	SpacialInformations::_height = height;
}
float SpacialInformations::getWidth() const
{
	return _width;
}
void SpacialInformations::setWidth(float width)
{
	SpacialInformations::_width = width;
}
float SpacialInformations::getCmx() const
{
	return _cmx;
}
void SpacialInformations::setCmx(float _cmx)
{
	SpacialInformations::_cmx = _cmx;
}
float SpacialInformations::getCmy() const
{
	return _cmy;
}
void SpacialInformations::setCmy(float _cmy)
{
	SpacialInformations::_cmy = _cmy;
}
float SpacialInformations::getAccx() const
{
	return _accx;
}
void SpacialInformations::setAccx(float _accx)
{
	SpacialInformations::_accx = _accx;
}
float SpacialInformations::getAccy() const
{
	return _accy;
}
void SpacialInformations::setAccy(float _accy)
{
	SpacialInformations::_accy = _accy;
}
SpacialInformations &
SpacialInformations::operator =(const SpacialInformations &spacialInformations)
{
	_x = spacialInformations.getX();
	_y = spacialInformations.getY();
	_mass = spacialInformations.getMass();
	_height = spacialInformations.getHeight();
	_width = spacialInformations.getWidth();
	_accx = spacialInformations.getAccx();
	_accy = spacialInformations.getAccy();
	_cmx = spacialInformations.getCmx();
	_cmy = spacialInformations.getCmy();
	
	return *this;
}
SpacialInformations::SpacialInformations()
{
	_x = 0;
	_y = 0;
	_mass = 0;
	_height = 0;
	_width = 0;
	_accx = 0;
	_accy = 0;
	_cmx = 0;
	_cmy = 0;
	
}

