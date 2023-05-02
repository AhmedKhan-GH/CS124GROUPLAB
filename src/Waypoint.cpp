#include "Waypoint.hpp"

Waypoint::Waypoint(std::string name, int x, int y) {
    this->name = name;
    this->x = x;
    this->y = y;
}

//"TODO"
std::string Waypoint::get_json() const {
    return "";
}

std::string Waypoint::get_name() const {
    return name;
}

int Waypoint::get_x() const {
    return x;
}

int Waypoint::get_y() const {
    return y;
}

//iterator and pointers used
int Waypoint::get_feature(std::string feature) const {
    auto it = features.find(feature);
    if (it != features.end()) 
    {
        return it->second;
    }
    else
    {
        std::cerr << "Error: Key not found in map\n";
        return -1;
    }
}

void Waypoint::add_feature(std::string feature, int val) {
    features[feature] = val;
}

//"TODO"
bool Waypoint::remove_feature(std::string feature) {

}

void Waypoint::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

void Waypoint::set_name(std::string name) {
    this->name = name;
}
