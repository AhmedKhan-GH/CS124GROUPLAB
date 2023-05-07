#ifndef WAYPOINT_HPP
#define WAYPOINT_HPP
#include <string>
class Waypoint
{
public:
	Waypoint(int y, int x, std::string name);
	std::string getName();
	int getX();
	int getY();
	void viewPoint();
private:
	int y;
	int x;
	std::string name;
	int uuid;
};

#endif //WAYPOINT_HPP
