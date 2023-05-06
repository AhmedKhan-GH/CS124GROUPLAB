#ifndef WAYSPACE_HPP
#define WAYSPACE_HPP
#include <iostream>
#include <cstdlib>
class Wayspace
{
public:
	Wayspace();
	void fillSpace(const char c);
	void printSpace();
	bool getActive();
	void plotRight(int y, int x, std::string input);
	void plotDown(int y, int x, std::string input);
	void activate();
	void deactivate();
	void setName(std::string name);
	void plotCompass();
	std::string getName();
private:
	//std::vector<Waypoint> waypoints;
	std::string name;
	bool active;
	char ascii_grid[22][80];
};


#endif //WAYSPACE_HPP
