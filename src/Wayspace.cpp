#include "Wayspace.hpp"

Wayspace::Wayspace() : active(false), scale_set(false), accumulator(0) {}

Wayspace::~Wayspace()
{
	for(auto& point : waypoints)
	{
		delete point;
	}
}

void Wayspace::listWaypoints()
{
	std::cout <<
	std::endl;
	for(auto& point : waypoints)
	{
		std::cout << point->getName() <<
		std::endl;
	}
}

void Wayspace::addWaypoint(int y, int x, std::string name)
{
	
	accumulator++;
	waypoints.push_back(new Waypoint(y, x, name, accumulator));
}

bool Wayspace::checkExistName(std::string name)
{
	bool exists = false;
	for(auto& point : waypoints)
	{
		if(point->getName() == name)
		{
			exists = true;
		}
	}
	return exists;
}

bool Wayspace::checkExistUUID(int uuid)
{
	bool exists = false;
	for(auto& point : waypoints)
	{
		if(point->getUUID() == uuid)
		{
			exists = true;
		}
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
	plotRight(1, 0, "<-+-> " + std::__cxx11::to_string(scale*5) + " " + unit + "(s)");
}

void Wayspace::plotHeaders()
{

	plotRight(0, 0, "[viewing '" + name  + "']");
	plotRight(21, 0, "['exitmap' to return]");
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
	//	waypoints.clear();
	name.clear();
	active = false;
	fillSpace(char(' '));
	scale = 0;
	scale_set = false;
	accumulator = 0;
}
