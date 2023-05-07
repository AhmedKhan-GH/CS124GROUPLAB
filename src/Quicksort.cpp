#include "Quicksort.hpp"


void Quicksort::quicksort(std::vector<Waypoint*>& a, std::string type)
{
    Quicksort::_quicksort(a, 0, a.size()-1, type);
}

int Quicksort::partition(std::vector<Waypoint*>& a, int from, int to, std::string type)
{
   double pivot = a[from]->getFeature(type);
   int i = from - 1;
   int j = to + 1;
   while (i < j)
   {
      i++; while (a[i]->getFeature(type) < pivot) { i++; }
      j--; while (a[j]->getFeature(type) > pivot) { j--; }
      if (i < j) { std::swap(a[i], a[j]); }
   }
   return j;
}

void Quicksort::_quicksort(std::vector<Waypoint*>& a, int from, int to, std::string type)
{
   if (from >= to) { return; }
   int p = Quicksort::partition(a, from, to, type);
   Quicksort::_quicksort(a, from, p, type);
   Quicksort::_quicksort(a, p + 1, to, type);
}