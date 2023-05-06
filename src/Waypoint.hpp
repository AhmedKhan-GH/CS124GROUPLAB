#ifndef WAYPOINT_HPP
#define WAYPOINT_HPP
#include <string>
class Waypoint
{
public:
	Waypoint(int y, int x, std::string name, int uuid);
	std::string getName();
	int getUUID();

	
private:
	int y;
	int x;
	std::string name;
	int uuid;
};

#endif //WAYPOINT_HPP
