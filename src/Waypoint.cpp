#include "Waypoint.hpp"

Waypoint::Waypoint(int y, int x, std::string name) : y(y), x(x), name(name) {}

void Waypoint::viewPoint()
{

}

std::string Waypoint::getName()
{
	return name;
}

int Waypoint::getX()
{
	return x;
}

int Waypoint::getY()
{
	return y;
}

