// src/algorithms/DijkstraRouter.cpp
#include "../../include/algorithms/DijkstraRouter.hpp"

namespace HEROS {
namespace Algorithms {

DijkstraRouter::DijkstraRouter() : hospitalMap(false) {}

DijkstraRouter::DijkstraRouter(const Graph& graph) : hospitalMap(graph) {}

std::vector<std::string> DijkstraRouter::findShortestPath(const std::string& start, 
                                                           const std::string& end) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    if (!hospitalMap.hasNode(start) || !hospitalMap.hasNode(end)) {
        lastMetrics.algorithmName = "Dijkstra";
        lastMetrics.complexity = "O((V+E) log V)";
        return std::vector<std::string>();
    }
    
    // Distance map
    std::unordered_map<std::string, double> distances;
    // Predecessor map for path reconstruction
    std::unordered_map<std::string, std::string> predecessors;
    // Visited set
    std::set<std::string> visited;
    
    // Initialize distances
    for (const auto& node : hospitalMap.getNodes()) {
        distances[node] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    
    // Min-heap priority queue
    DataStructures::MinHeap<DijkstraNode> pq;
    pq.insert(DijkstraNode(start, 0));
    
    size_t operationsCount = 0;
    
    while (!pq.isEmpty()) {
        DijkstraNode current = pq.extractMin();
        operationsCount++;
        
        if (visited.count(current.nodeId)) {
            continue;
        }
        visited.insert(current.nodeId);
        
        // Found destination
        if (current.nodeId == end) {
            break;
        }
        
        // Process neighbors
        for (const auto& edge : hospitalMap.getEdgesFrom(current.nodeId)) {
            if (visited.count(edge.to)) continue;
            
            double newDist = distances[current.nodeId] + edge.weight;
            
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                predecessors[edge.to] = current.nodeId;
                pq.insert(DijkstraNode(edge.to, newDist));
                operationsCount++;
            }
        }
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    // Record metrics
    lastMetrics.algorithmName = "Dijkstra";
    lastMetrics.complexity = "O((V+E) log V)";
    lastMetrics.executionTimeMs = std::chrono::duration<double, std::milli>(
        endTime - startTime).count();
    lastMetrics.operationsCount = operationsCount;
    
    // Reconstruct path
    return reconstructPath(predecessors, start, end);
}

std::vector<std::string> DijkstraRouter::reconstructPath(
    const std::unordered_map<std::string, std::string>& predecessors,
    const std::string& start,
    const std::string& end) {
    
    std::vector<std::string> path;
    
    if (predecessors.find(end) == predecessors.end() && start != end) {
        return path; // No path found
    }
    
    std::string current = end;
    while (current != start) {
        path.push_back(current);
        if (predecessors.find(current) == predecessors.end()) {
            return std::vector<std::string>(); // No path
        }
        current = predecessors.at(current);
    }
    path.push_back(start);
    
    // Reverse to get path from start to end
    std::reverse(path.begin(), path.end());
    
    return path;
}

double DijkstraRouter::getShortestDistance(const std::string& start, 
                                            const std::string& end) {
    auto allPaths = findAllShortestPaths(start);
    if (allPaths.find(end) != allPaths.end()) {
        return allPaths[end];
    }
    return std::numeric_limits<double>::infinity();
}

std::unordered_map<std::string, double> DijkstraRouter::findAllShortestPaths(
    const std::string& start) {
    
    std::unordered_map<std::string, double> distances;
    std::set<std::string> visited;
    
    for (const auto& node : hospitalMap.getNodes()) {
        distances[node] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    
    DataStructures::MinHeap<DijkstraNode> pq;
    pq.insert(DijkstraNode(start, 0));
    
    while (!pq.isEmpty()) {
        DijkstraNode current = pq.extractMin();
        
        if (visited.count(current.nodeId)) continue;
        visited.insert(current.nodeId);
        
        for (const auto& edge : hospitalMap.getEdgesFrom(current.nodeId)) {
            double newDist = distances[current.nodeId] + edge.weight;
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                pq.insert(DijkstraNode(edge.to, newDist));
            }
        }
    }
    
    return distances;
}

std::vector<std::string> DijkstraRouter::findPathToNearestDestination(
    const std::string& start,
    const std::vector<std::string>& destinations) {
    
    auto allDistances = findAllShortestPaths(start);
    
    std::string nearest;
    double minDist = std::numeric_limits<double>::infinity();
    
    for (const auto& dest : destinations) {
        if (allDistances.find(dest) != allDistances.end() && 
            allDistances[dest] < minDist) {
            minDist = allDistances[dest];
            nearest = dest;
        }
    }
    
    if (nearest.empty()) {
        return std::vector<std::string>();
    }
    
    return findShortestPath(start, nearest);
}

bool DijkstraRouter::isReachable(const std::string& start, const std::string& end) {
    auto path = findShortestPath(start, end);
    return !path.empty();
}

void DijkstraRouter::printPath(const std::vector<std::string>& path) const {
    if (path.empty()) {
        std::cout << "No path found." << std::endl;
        return;
    }
    
    std::cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "Total distance: " << calculatePathDistance(path) << std::endl;
}

double DijkstraRouter::calculatePathDistance(const std::vector<std::string>& path) const {
    if (path.size() < 2) return 0;
    
    double total = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        total += hospitalMap.getEdgeWeight(path[i], path[i + 1]);
    }
    return total;
}

} // namespace Algorithms
} // namespace HEROS