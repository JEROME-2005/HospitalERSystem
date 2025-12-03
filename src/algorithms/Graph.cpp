#include "../../include/algorithms/Graph.hpp"
#include <iostream>
#include <iomanip>  // ADD THIS LINE
#include <cmath>
#include <algorithm>

Graph::Graph() : vertexCount(0), edgeCount(0) {}

void Graph::addNode(const std::string& nodeId, const Coordinates& position) {
    if (nodePositions.find(nodeId) == nodePositions.end()) {
        nodePositions[nodeId] = position;
        adjacencyList[nodeId] = std::vector<Edge>();
        vertexCount++;
    }
}

void Graph::addEdge(const std::string& from, const std::string& to, double weight) {
    adjacencyList[from].push_back(Edge(from, to, weight));
    edgeCount++;
}

void Graph::addBidirectionalEdge(const std::string& node1, const std::string& node2, double weight) {
    addEdge(node1, node2, weight);
    addEdge(node2, node1, weight);
}

std::vector<Edge> Graph::getEdges(const std::string& node) const {
    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        return it->second;
    }
    return std::vector<Edge>();
}

std::vector<std::string> Graph::getAllNodes() const {
    std::vector<std::string> nodes;
    for (const auto& pair : nodePositions) {
        nodes.push_back(pair.first);
    }
    return nodes;
}

std::vector<Edge> Graph::getAllEdges() const {
    std::vector<Edge> allEdges;
    for (const auto& pair : adjacencyList) {
        for (const Edge& edge : pair.second) {
            allEdges.push_back(edge);
        }
    }
    return allEdges;
}

Coordinates Graph::getNodePosition(const std::string& node) const {
    auto it = nodePositions.find(node);
    if (it != nodePositions.end()) {
        return it->second;
    }
    return Coordinates();
}

bool Graph::hasNode(const std::string& node) const {
    return nodePositions.find(node) != nodePositions.end();
}

double Graph::calculateEuclideanDistance(const std::string& node1, const std::string& node2) const {
    Coordinates pos1 = getNodePosition(node1);
    Coordinates pos2 = getNodePosition(node2);
    
    double dx = pos2.x - pos1.x;
    double dy = pos2.y - pos1.y;
    
    return std::sqrt(dx * dx + dy * dy);
}

void Graph::display() const {
    std::cout << "\n╔══════════════════════════��═════════════════════╗\n";
    std::cout << "║           HOSPITAL LAYOUT GRAPH                ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    std::cout << "║ Vertices (Rooms): " << std::setw(28) << vertexCount << " ║\n";
    std::cout << "║ Edges (Corridors): " << std::setw(27) << edgeCount << " ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    
    std::cout << "\nAdjacency List:\n";
    for (const auto& pair : adjacencyList) {
        std::cout << pair.first << " → ";
        for (const Edge& edge : pair.second) {
            std::cout << edge.to << "(" << edge.weight << "m) ";
        }
        std::cout << "\n";
    }
}