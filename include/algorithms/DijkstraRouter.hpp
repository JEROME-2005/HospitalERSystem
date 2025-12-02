// include/algorithms/DijkstraRouter.hpp
#ifndef DIJKSTRA_ROUTER_HPP
#define DIJKSTRA_ROUTER_HPP

#include "Graph.hpp"
#include "../data_structures/MinHeap.hpp"

namespace HEROS {
namespace Algorithms {

/**
 * DijkstraRouter - Shortest Path Finding using Dijkstra's Algorithm
 * 
 * Time Complexity: O((V + E) log V) using min-heap
 * Space Complexity: O(V)
 * 
 * Used for finding fastest routes for medical staff in hospital.
 */
class DijkstraRouter {
private:
    Graph hospitalMap;
    
    struct DijkstraNode {
        std::string nodeId;
        double distance;
        
        DijkstraNode() : distance(std::numeric_limits<double>::infinity()) {}
        DijkstraNode(const std::string& id, double dist) : nodeId(id), distance(dist) {}
        
        bool operator<(const DijkstraNode& other) const {
            return distance < other.distance;
        }
        
        bool operator>(const DijkstraNode& other) const {
            return distance > other.distance;
        }
    };

public:
    // Constructors
    DijkstraRouter();
    DijkstraRouter(const Graph& graph);
    
    // Destructor
    ~DijkstraRouter() = default;
    
    // Set the hospital map
    void setGraph(const Graph& graph) { hospitalMap = graph; }
    Graph getGraph() const { return hospitalMap; }
    
    // Core routing functions
    std::vector<std::string> findShortestPath(const std::string& start, 
                                               const std::string& end);
    
    double getShortestDistance(const std::string& start, 
                               const std::string& end);
    
    std::unordered_map<std::string, double> findAllShortestPaths(const std::string& start);
    
    // Multi-destination routing
    std::vector<std::string> findPathToNearestDestination(
        const std::string& start,
        const std::vector<std::string>& destinations);
    
    // Utility
    bool isReachable(const std::string& start, const std::string& end);
    void printPath(const std::vector<std::string>& path) const;
    double calculatePathDistance(const std::vector<std::string>& path) const;
    
    // Performance metrics
    PerformanceMetrics getLastOperationMetrics() const { return lastMetrics; }

private:
    PerformanceMetrics lastMetrics;
    
    std::vector<std::string> reconstructPath(
        const std::unordered_map<std::string, std::string>& predecessors,
        const std::string& start,
        const std::string& end);
};

} // namespace Algorithms
} // namespace HEROS

#endif // DIJKSTRA_ROUTER_HPP