#include "../../include/algorithms/DijkstraRouter.hpp"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <iomanip>

DijkstraRouter::DijkstraRouter(Graph* graph) : hospitalMap(graph) {}

RouteInfo DijkstraRouter::findShortestPath(const std::string& start, const std::string& end) {
    RouteInfo result;
    
    if (!hospitalMap->hasNode(start) || !hospitalMap->hasNode(end)) {
        std::cout << "Error: Start or end node not found in graph!\n";
        return result;
    }
    
    // Priority queue: min-heap based on distance
    std::priority_queue<DijkstraNode, std::vector<DijkstraNode>, std::greater<DijkstraNode>> pq;
    
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous;
    std::unordered_map<std::string, bool> visited;
    
    // Initialize distances
    for (const std::string& node : hospitalMap->getAllNodes()) {
        distances[node] = std::numeric_limits<double>::infinity();
        visited[node] = false;
    }
    
    distances[start] = 0.0;
    pq.push(DijkstraNode(start, 0.0));
    
    // Dijkstra's algorithm: O((V+E) log V)
    while (!pq.empty()) {
        DijkstraNode current = pq.top();
        pq.pop();
        
        if (visited[current.id]) continue;
        visited[current.id] = true;
        
        if (current.id == end) break;
        
        // Explore neighbors
        for (const Edge& edge : hospitalMap->getEdges(current.id)) {
            double newDist = distances[current.id] + edge.weight;
            
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                previous[edge.to] = current.id;
                pq.push(DijkstraNode(edge.to, newDist));
            }
        }
    }
    
    // Reconstruct path
    if (distances[end] != std::numeric_limits<double>::infinity()) {
        std::vector<std::string> path;
        std::string current = end;
        
        while (current != start) {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(start);
        
        std::reverse(path.begin(), path.end());
        
        result.path = path;
        result.totalDistance = distances[end];
        result.nodeCount = path.size();
    }
    
    return result;
}

std::vector<RouteInfo> DijkstraRouter::findPathsToMultipleDestinations(
    const std::string& start, 
    const std::vector<std::string>& destinations) {
    
    std::vector<RouteInfo> routes;
    for (const std::string& dest : destinations) {
        routes.push_back(findShortestPath(start, dest));
    }
    return routes;
}

void DijkstraRouter::displayRoute(const RouteInfo& route) const {
    if (route.path.empty()) {
        std::cout << "No route found!\n";
        return;
    }
    
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║              OPTIMAL ROUTE                     ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    std::cout << "║ Total Distance: " << std::setw(30) << std::fixed 
              << std::setprecision(2) << route.totalDistance << "m ║\n";
    std::cout << "║ Number of Stops: " << std::setw(29) << route.nodeCount << " ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    
    std::cout << "\nPath: ";
    for (size_t i = 0; i < route.path.size(); i++) {
        std::cout << route.path[i];
        if (i < route.path.size() - 1) std::cout << " → ";
    }
    std::cout << "\n";
}