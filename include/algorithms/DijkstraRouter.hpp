#ifndef DIJKSTRA_ROUTER_HPP
#define DIJKSTRA_ROUTER_HPP

#include "Graph.hpp"
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <utility>

namespace Algorithms {

    /**
     * Path Result Structure
     * Contains the result of a shortest path query
     */
    struct PathResult {
        std::vector<std::string> path;
        double totalDistance;
        bool pathFound;
        int nodesVisited;
        double computationTimeMs;

        PathResult() : totalDistance(0), pathFound(false), nodesVisited(0), computationTimeMs(0) {}
    };

    /**
     * DijkstraRouter Class
     * 
     * Implements Dijkstra's algorithm for finding shortest paths in hospital layout.
     * 
     * Use Cases:
     * - Find fastest route for doctors to reach patients
     * - Optimize staff movement during emergencies
     * - Calculate distances for resource allocation
     * 
     * Time Complexity: O((V + E) log V) using adjacency list + min-heap
     * Space Complexity: O(V) for distance and predecessor arrays
     */
    class DijkstraRouter {
    private:
        Graph* hospitalMap;
        std::map<std::string, double> distances;
        std::map<std::string, std::string> predecessors;
        std::map<std::string, bool> visited;
        
        // Performance Metrics
        int lastNodesVisited;
        double lastComputationTime;

        // Priority queue element
        typedef std::pair<double, std::string> PQElement;

    public:
        // Constructors
        DijkstraRouter();
        DijkstraRouter(Graph* graph);
        DijkstraRouter(const DijkstraRouter& other);
        
        // Destructor
        ~DijkstraRouter();

        // Assignment operator
        DijkstraRouter& operator=(const DijkstraRouter& other);

        // Graph Management
        void setGraph(Graph* graph) { hospitalMap = graph; }
        Graph* getGraph() const { return hospitalMap; }

        // Core Dijkstra Operations
        PathResult findShortestPath(const std::string& start, const std::string& end);
        std::map<std::string, double> findAllShortestPaths(const std::string& start);
        
        // Multi-destination routing
        PathResult findShortestPathToAny(const std::string& start, 
                                         const std::vector<std::string>& destinations);
        
        // Route optimization
        std::vector<std::string> findOptimalRoute(const std::string& start,
                                                  const std::vector<std::string>& waypoints);

        // Distance Queries
        double getDistance(const std::string& from, const std::string& to);
        bool isReachable(const std::string& from, const std::string& to);
        
        // Path Reconstruction
        std::vector<std::string> reconstructPath(const std::string& start, 
                                                  const std::string& end);

        // Performance Metrics
        int getLastNodesVisited() const { return lastNodesVisited; }
        double getLastComputationTime() const { return lastComputationTime; }
        
        // Utility Methods
        void reset();
        void displayDistances() const;
        std::string getComplexityAnalysis() const;

    private:
        // Helper Methods
        void initializeSingleSource(const std::string& source);
        void relax(const std::string& u, const std::string& v, double weight);
    };

} // namespace Algorithms

#endif // DIJKSTRA_ROUTER_HPP