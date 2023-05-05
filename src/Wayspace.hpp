#ifndef WAYSPACE_HPP
#define WAYSPACE_HPP
#include <iostream>
#include <cstdlib>
class Wayspace
{
public:
	Wayspace();
	void fillMap(const char c);
	void printMap();
private:
	const int width;
	const int height;
	char ascii_map[24][80];
};


#endif //WAYSPACE_HPP
