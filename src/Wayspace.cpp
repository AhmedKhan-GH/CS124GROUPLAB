#include "Wayspace.hpp"

Wayspace::Wayspace() : active(false), scale_set(false) {}

Wayspace::~Wayspace()
{
	for(Waypoint* point : waypoint_vec)
	{
		point = nullptr;
	}
	waypoint_map.~hashmap()
}

void Wayspace::listWaypoints()
{
	std::cout <<
	std::endl;

	if(waypoint_vec.empty())
	{
		std::cout <<
		std::endl << "no waypoints in map" <<
		std::endl;
	}

	for(Waypoint* point : waypoint_vec)
	{
		std::cout << point->getName() << " : <" <<  point->getY() << "," << point->getX() << ">" << std::endl;
	}
}

void Wayspace::viewPoint(std::string name)
{
	Waypoint* point = waypoint_map.find(name);
	point->viewPoint();
}

void Wayspace::plotPoints()
{
	for(Waypoint* point : waypoint_vec)
	{
		plotRight(point->getY(), point->getX(), "@"+point->getName());
	}
}

void Wayspace::addWaypoint(int y, int x, std::string name)
{
	Waypoint* new_point = new Waypoint(y, x, name);
	waypoint_vec.push_back(new_point);
	waypoint_map.insert(new_point);
}

bool Wayspace::checkExistName(std::string name)
{
	bool exists = true;
	if (waypoint_map.find(name) == nullptr)
	{
		exists = false;
	}
	return exists;
}

void Wayspace::setScale(int scale)
{
	this->scale = scale;
	scale_set = true;
}

bool Wayspace::getScaleSet()
{
	return this->scale_set;
}

void Wayspace::setUnit(std::string unit)
{
	this->unit = unit;
}

std::string Wayspace::getUnit()
{
	return this->unit;
}

int Wayspace::getScale()
{
	return this->scale;
}


void Wayspace::plotCompass()
{
	plotRight(2, 75, "<W+E>");
	plotDown(0, 77, "^N+Sv");
}

void Wayspace::plotScale()
{
	plotRight(1, 0, "<-+-> " + std::to_string(scale*5) + " " + unit + "(s)");
}

void Wayspace::plotHeaders()
{

	plotRight(0, 0, "(viewing '" + name  + "')");
	plotRight(21, 0, "('exitmap' to return)");
}

void Wayspace::plotRight(int y, int x, std::string input)
{
	for(int i = 0; i < input.length(); i++)
	{
		ascii_grid[y][x+i] = input[i];
	}
}

void Wayspace::plotDown(int y, int x, std::string input)
{
	for(int i = 0; i < input.length(); i++)
	{
		ascii_grid[y+i][x] = input[i];
	}
}

void Wayspace::fillSpace(const char c)
{
	for(auto& row : ascii_grid)
	{
		for(char& point : row)
		{
			point = c;
		}
	}
}

bool Wayspace::getActive()
{
	return this->active;
}

void Wayspace::printSpace()
{
	system("clear");
	for(auto& row : ascii_grid)
	{
		for(char& point : row)
		{
			std::cout << point;
		}
		std::cout << std::endl;
	}
}

void Wayspace::setName(std::string name)
{
	this->name = name;
}

void Wayspace::activate()
{
	this->active = true;
}

std::string Wayspace::getName()
{
	return this->name;
}

void Wayspace::deactivate()
{
	//	waypoint_vec.clear();
	name.clear();
	active = false;
	fillSpace(char(' '));
	scale = 0;
	scale_set = false;
}
