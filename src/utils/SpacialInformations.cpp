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
}

double SpacialInformations::getX() const
{
	return _x;
}
void SpacialInformations::setX(double x)
{
	SpacialInformations::_x = x;
}
double SpacialInformations::getY() const
{
	return _y;
}
void SpacialInformations::setY(double y)
{
	SpacialInformations::_y = y;
}
double SpacialInformations::getMass() const
{
	return _mass;
}
void SpacialInformations::setMass(double mass)
{
	SpacialInformations::_mass = mass;
}
double SpacialInformations::getHeight() const
{
	return _height;
}
void SpacialInformations::setHeight(double height)
{
	SpacialInformations::_height = height;
}
double SpacialInformations::getWidth() const
{
	return _width;
}
void SpacialInformations::setWidth(double width)
{
	SpacialInformations::_width = width;
}
double SpacialInformations::getCmx() const
{
	return _cmx;
}
void SpacialInformations::setCmx(double _cmx)
{
	SpacialInformations::_cmx = _cmx;
}
double SpacialInformations::getCmy() const
{
	return _cmy;
}
void SpacialInformations::setCmy(double _cmy)
{
	SpacialInformations::_cmy = _cmy;
}
double SpacialInformations::getAccx() const
{
	return _accx;
}
void SpacialInformations::setAccx(double _accx)
{
	SpacialInformations::_accx = _accx;
}
double SpacialInformations::getAccy() const
{
	return _accy;
}
void SpacialInformations::setAccy(double _accy)
{
	SpacialInformations::_accy = _accy;
}

