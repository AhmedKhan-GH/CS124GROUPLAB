#ifndef WAYSPACE_HPP
#define WAYSPACE_HPP
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include "Waypoint.hpp"
#include "Hashmap.hpp"
#include "Quicksort.hpp"
#include "Stack.hpp"
#include <algorithm>
class Wayspace
{
public:
	Wayspace();
	~Wayspace();

	void fillSpace(const char c);
	void printSpace();

	void undoAdd();
	void addPoint(int y, int x, std::string name);
	void listPoints();
	void viewPoint(std::string name);

	void pushFeature(std::string point, std::string type, double metric);
	void pullFeature(std::string point, std::string type);
	void rankFeatures(std::string type);

	void activate();
	void deactivate();

	int getScale();
	bool getActive();
	bool getScaleSet();
	std::string getName();
	std::string getUnit();

	void plotRight(int y, int x, std::string input);
	void plotDown(int y, int x, std::string input);

	void plotElements();
	void plotPoints();

	bool checkExistName(std::string name);

	void setScale(int scale);
	void setName(std::string name);
	void setUnit(std::string unit);

private:
	int scale;
	std::string name;
	std::string unit;

	bool active;
	bool scale_set;

	char ascii_grid[22][80];
	std::vector<Waypoint*> waypoint_vec;
	Stack waypoint_stack;
	Hashmap waypoint_map;
};


#endif //WAYSPACE_HPP
