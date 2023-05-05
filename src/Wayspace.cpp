#include "Wayspace.hpp"

Wayspace::Wayspace() : width(80), height(22) {};

void Wayspace::fillMap(const char c)
{
	for(auto& row : ascii_map)
	{
		for(char& element : row)
		{
			element = c;
		}
	}	
}

void Wayspace::printMap()
{
	system("clear");
	for(auto& row : ascii_map)
	{	
		for(char& element : row)
		{
			std::cout << element;
		}
		std::cout << std::endl;
	}
}

