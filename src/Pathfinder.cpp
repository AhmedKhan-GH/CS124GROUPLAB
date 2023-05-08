#include "Pathfinder.hpp"

double Pathfinder::distance(Waypoint* a, Waypoint* b) {
        int dx = a->getX() - b->getX();
        int dy = a->getY() - b->getY();
    return std::sqrt(dx * dx + dy * dy);
}

Pathfinder::Pathfinder(const std::vector<Waypoint*>& waypoints)
{
    for(const auto& point1 : waypoints){
        for(const auto& point2 : waypoints){
            if(point1 != point2)
            {
                graph[point1->getName()][point2->getName()] = distance(point1, point2);
            }
        }
    }
}

std::vector<std::string> Pathfinder::reconstruct_path(std::unordered_map<std::string, std::string>& came_from, const std::string& start, const std::string& end) {
        std::vector<std::string> path;
        std::string current = end;

        while (current != start) {
            path.push_back(current);
            current = came_from[current];
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return path;
    }

 std::pair<std::string, double> Pathfinder::get_second_shortest_edge(const std::string& node) 
 {
    if (graph[node].size() < 2) {
        return {"", std::numeric_limits<double>::max()};
    }

    std::vector<std::pair<std::string, double>> edges(graph[node].begin(), graph[node].end());
    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    return edges[1];
}

std::vector<std::string> Pathfinder::find_alternative_path(const std::string& start, const std::string& end)
{
    std::set<std::string> visited;
    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> came_from;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        if (current == end) {
            return reconstruct_path(came_from, start, end);
        }

        auto second_shortest_edge = get_second_shortest_edge(current);

        for (const auto& [neighbor, _] : graph[current]) {
            if (current == start && neighbor == end) {
                continue;  // Ignore the direct edge between start and end nodes
            }

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
                came_from[neighbor] = current;
                if (neighbor == second_shortest_edge.first) {
                    break;
                }
            }
        }
    }

    // No alternative path found
    return {};
}

