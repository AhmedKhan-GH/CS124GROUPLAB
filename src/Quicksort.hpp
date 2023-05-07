#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
#include "Waypoint.hpp"
#include <vector>
#include <string>

class Quicksort
{
public:

    static int partition(std::vector<Waypoint*>& a, int from, int to, std::string type);
    static void quicksort(std::vector<Waypoint*>& a, std::string type);
    static void _quicksort(std::vector<Waypoint*>& a, int from, int to, std::string type);
};

#endif //QUICKSORT_HPP