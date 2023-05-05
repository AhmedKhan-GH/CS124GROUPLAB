#include "Wayspace.hpp"

Wayspace::Wayspace() : active(false){}

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
}
