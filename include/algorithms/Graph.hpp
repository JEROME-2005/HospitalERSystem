#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "../core/HospitalRoom.hpp"

struct Edge {
    std::string from;
    std::string to;
    double weight;
    
    Edge() : weight(0.0) {}
    Edge(const std::string& f, const std::string& t, double w) 
        : from(f), to(t), weight(w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    std::unordered_map<std::string, Coordinates> nodePositions;
    int vertexCount;
    int edgeCount;

public:
    Graph();
    
    // Graph construction
    void addNode(const std::string& nodeId, const Coordinates& position);
    void addEdge(const std::string& from, const std::string& to, double weight);
    void addBidirectionalEdge(const std::string& node1, const std::string& node2, double weight);
    
    // Getters
    std::vector<Edge> getEdges(const std::string& node) const;
    std::vector<std::string> getAllNodes() const;
    std::vector<Edge> getAllEdges() const;
    Coordinates getNodePosition(const std::string& node) const;
    int getVertexCount() const { return vertexCount; }
    int getEdgeCount() const { return edgeCount; }
    bool hasNode(const std::string& node) const;
    
    // Utility
    void display() const;
    double calculateEuclideanDistance(const std::string& node1, const std::string& node2) const;
};

#endif // GRAPH_HPP