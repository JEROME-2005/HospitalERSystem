#ifndef DIJKSTRA_ROUTER_HPP
#define DIJKSTRA_ROUTER_HPP

#include "Graph.hpp"
#include <vector>
#include <string>
#include <limits>

struct RouteInfo {
    std::vector<std::string> path;
    double totalDistance;
    int nodeCount;
    
    RouteInfo() : totalDistance(0.0), nodeCount(0) {}
};

class DijkstraRouter {
private:
    Graph* hospitalMap;
    
    struct DijkstraNode {
        std::string id;
        double distance;
        
        DijkstraNode(const std::string& nodeId, double dist) 
            : id(nodeId), distance(dist) {}
        
        bool operator>(const DijkstraNode& other) const {
            return distance > other.distance;
        }
    };

public:
    DijkstraRouter(Graph* graph);
    
    // Main algorithm - O((V+E) log V) complexity
    RouteInfo findShortestPath(const std::string& start, const std::string& end);
    
    // Multiple destinations
    std::vector<RouteInfo> findPathsToMultipleDestinations(
        const std::string& start, 
        const std::vector<std::string>& destinations
    );
    
    // Utility
    void displayRoute(const RouteInfo& route) const;
};

#endif // DIJKSTRA_ROUTER_HPP