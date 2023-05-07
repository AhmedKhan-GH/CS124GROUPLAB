#ifndef WAYPOINT_HPP
#define WAYPOINT_HPP
#include <iostream>
#include <unordered_map>
class Waypoint
{
public:
	Waypoint(int y, int x, std::string name);
	std::string getName();
	int getX();
	int getY();
	void viewPoint();
	void addFeature(std::string type, double metric);
	double getFeature(std::string type);
	void removeFeature(std::string type);
	bool checkFeature(std::string type);
private:
	int y;
	int x;
	std::string name;
	std::unordered_map<std::string, double> features;

};

#endif //WAYPOINT_HPP
