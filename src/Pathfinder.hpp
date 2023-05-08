#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
#include "Waypoint.hpp"
#include <vector>
#include <cmath>
#include <queue>
#include <list>
#include <unordered_map>
#include <limits>
#include <set>
#include <algorithm>

class Pathfinder
{
public:
    Pathfinder(const std::vector<Waypoint*>& waypoints);

    std::pair<std::string, double> get_second_shortest_edge(const std::string& node);
    std::vector<std::string> reconstruct_path(std::unordered_map<std::string, std::string>& came_from, const std::string& start, const std::string& end);
    std::vector<std::string> find_alternative_path(const std::string& start, const std::string& end);

private:
    double distance(Waypoint* a, Waypoint* b);
    std::unordered_map<std::string, std::unordered_map<std::string, double>> graph;
};



#endif //PATHFINDER_HPP
