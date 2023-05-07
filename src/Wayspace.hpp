#ifndef WAYSPACE_HPP
#define WAYSPACE_HPP
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include "Waypoint.hpp"
class Wayspace
{
public:
	Wayspace();
	~Wayspace();

	void fillSpace(const char c);
	void printSpace();
	
	void addWaypoint(int y, int x, std::string name);
	void listWaypoints();
	void viewPoint(std::string name);

	void activate();
	void deactivate();

	int getScale();
	bool getActive();
	bool getScaleSet();
	std::string getName();
	std::string getUnit();

	void plotRight(int y, int x, std::string input);
	void plotDown(int y, int x, std::string input);

	void plotCompass();
	void plotHeaders();
	void plotScale();
	void plotPoints();

	bool checkExistName(std::string name);
	bool checkExistUUID(int uuid);

	void setScale(int scale);
	void setName(std::string name);
	void setUnit(std::string unit);

	std::string encodeUUID(int uuid);
	int decodeUUID(std::string coda);

private:
	int accumulator;
	int scale;
	std::string name;
	std::string unit;

	bool active;
	bool scale_set;

	char ascii_grid[22][80];
	std::vector<Waypoint*> waypoints;
};


#endif //WAYSPACE_HPP
