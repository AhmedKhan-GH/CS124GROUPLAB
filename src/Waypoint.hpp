#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <string>
#include <unordered_map>

class Waypoint {
private:
    std::string name;
    int x;
    int y;
    unordered_map<string, int> features;

public:
    Waypoint();
    Waypoint(std::string name, int x, int y);

    std::string get_json() const;
    std::string get_name() const;
    int get_x() const;
    int get_y() const;
    int get_feature(std::string feature) const;

    void add_feature(std::string feature, int val);
    bool remove_feature(std::string feature);
    void set_position(int x, int y);
    void set_name(std::string name);
};

#endif
