#include "Waypoint.hpp"

Waypoint::Waypoint(int y, int x, std::string name, int uuid) : y(y), x(x), name(name), uuid(uuid) {}

std::string Waypoint::getName()
{
	return name;
}

int Waypoint::getUUID()
{
	return uuid;
}


