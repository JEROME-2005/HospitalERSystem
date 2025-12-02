// include/algorithms/Graph.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {
namespace Algorithms {

/**
 * Graph - Weighted Graph Implementation using Adjacency List
 * 
 * Used for representing hospital corridors and room connections.
 * Supports both directed and undirected edges.
 */
class Graph {
private:
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    std::unordered_map<std::string, Coordinates> nodePositions;
    bool isDirected;
    int edgeCount;

public:
    // Constructors
    Graph(bool directed = false);
    
    // Destructor
    ~Graph() = default;
    
    // Node operations
    void addNode(const std::string& nodeId);
    void addNode(const std::string& nodeId, const Coordinates& position);
    bool hasNode(const std::string& nodeId) const;
    void removeNode(const std::string& nodeId);
    
    // Edge operations
    void addEdge(const std::string& from, const std::string& to, double weight);
    void addEdge(const Edge& edge);
    bool hasEdge(const std::string& from, const std::string& to) const;
    void removeEdge(const std::string& from, const std::string& to);
    double getEdgeWeight(const std::string& from, const std::string& to) const;
    
    // Getters
    std::vector<std::string> getNodes() const;
    std::vector<Edge> getEdges() const;
    std::vector<Edge> getEdgesFrom(const std::string& nodeId) const;
    std::vector<std::string> getNeighbors(const std::string& nodeId) const;
    Coordinates getNodePosition(const std::string& nodeId) const;
    int getNodeCount() const { return static_cast<int>(adjacencyList.size()); }
    int getEdgeCount() const { return edgeCount; }
    bool getIsDirected() const { return isDirected; }
    
    // Utility
    void clear();
    void printGraph() const;
    std::string toString() const;
    
    // Graph operations
    Graph getSubgraph(const std::vector<std::string>& nodes) const;
    double getTotalWeight() const;
};

} // namespace Algorithms
} // namespace HEROS

#endif // GRAPH_HPP