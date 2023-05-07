#include "Waypoint.hpp"

Waypoint::Waypoint(int y, int x, std::string name) : y(y), x(x), name(name) {}

void Waypoint::viewPoint()
{
	std::cout << std::endl << name << " : <" << y << "," << x << ">" << std::endl;
	for(auto& elem : features)
	{
		std::cout << elem.first << ": " << elem.second << std::endl;
	}
}

//iterator and pointers used
double Waypoint::getFeature(std::string type) 
{
    auto it = features.find(type);
    if (it != features.end()) 
    {
        return it->second;
    }
    return 0;
}

bool Waypoint::checkFeature(std::string type)
{
    return features.count(type);
}

void Waypoint::addFeature(std::string type, double metric)
{
    features.insert({type, metric});
}

void Waypoint::removeFeature(std::string type)
{
    auto it = features.find(type);
    if (it != features.end()) 
    {
        features.erase(it);
    }
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

