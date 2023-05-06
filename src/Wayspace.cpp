#include "Wayspace.hpp"

Wayspace::Wayspace() : active(false){}

void Wayspace::plotCompass()
{
	plotRight(2, 75, "<W+E>");
	plotDown(0, 77, "^N+Sv");
}

void Wayspace::plotHeaders()
{

	plotRight(0, 0, "[viewing '" + space.getName() + "']");
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
}
