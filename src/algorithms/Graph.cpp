// src/algorithms/Graph.cpp
#include "../../include/algorithms/Graph.hpp"

namespace HEROS {
namespace Algorithms {

Graph::Graph(bool directed) : isDirected(directed), edgeCount(0) {}

void Graph::addNode(const std::string& nodeId) {
    if (!hasNode(nodeId)) {
        adjacencyList[nodeId] = std::vector<Edge>();
        nodePositions[nodeId] = Coordinates();
    }
}

void Graph::addNode(const std::string& nodeId, const Coordinates& position) {
    addNode(nodeId);
    nodePositions[nodeId] = position;
}

bool Graph::hasNode(const std::string& nodeId) const {
    return adjacencyList.find(nodeId) != adjacencyList.end();
}

void Graph::removeNode(const std::string& nodeId) {
    if (!hasNode(nodeId)) return;
    
    // Remove all edges to this node
    for (auto& pair : adjacencyList) {
        auto& edges = pair.second;
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [&nodeId](const Edge& e) { return e.to == nodeId; }),
            edges.end()
        );
    }
    
    // Remove the node
    edgeCount -= static_cast<int>(adjacencyList[nodeId].size());
    adjacencyList.erase(nodeId);
    nodePositions.erase(nodeId);
}

void Graph::addEdge(const std::string& from, const std::string& to, double weight) {
    // Ensure nodes exist
    addNode(from);
    addNode(to);
    
    // Check if edge already exists
    if (!hasEdge(from, to)) {
        adjacencyList[from].push_back(Edge(from, to, weight));
        edgeCount++;
        
        if (!isDirected && !hasEdge(to, from)) {
            adjacencyList[to].push_back(Edge(to, from, weight));
        }
    }
}

void Graph::addEdge(const Edge& edge) {
    addEdge(edge.from, edge.to, edge.weight);
}

bool Graph::hasEdge(const std::string& from, const std::string& to) const {
    if (!hasNode(from)) return false;
    
    const auto& edges = adjacencyList.at(from);
    for (const auto& edge : edges) {
        if (edge.to == to) return true;
    }
    return false;
}

void Graph::removeEdge(const std::string& from, const std::string& to) {
    if (!hasNode(from)) return;
    
    auto& edges = adjacencyList[from];
    auto it = std::remove_if(edges.begin(), edges.end(),
        [&to](const Edge& e) { return e.to == to; });
    
    if (it != edges.end()) {
        edges.erase(it, edges.end());
        edgeCount--;
        
        if (!isDirected) {
            removeEdge(to, from);
        }
    }
}

double Graph::getEdgeWeight(const std::string& from, const std::string& to) const {
    if (!hasNode(from)) {
        throw std::runtime_error("Node not found: " + from);
    }
    
    const auto& edges = adjacencyList.at(from);
    for (const auto& edge : edges) {
        if (edge.to == to) return edge.weight;
    }
    
    throw std::runtime_error("Edge not found: " + from + " -> " + to);
}

std::vector<std::string> Graph::getNodes() const {
    std::vector<std::string> nodes;
    for (const auto& pair : adjacencyList) {
        nodes.push_back(pair.first);
    }
    return nodes;
}

std::vector<Edge> Graph::getEdges() const {
    std::vector<Edge> edges;
    std::set<std::pair<std::string, std::string>> seen;
    
    for (const auto& pair : adjacencyList) {
        for (const auto& edge : pair.second) {
            auto key = std::make_pair(
                std::min(edge.from, edge.to),
                std::max(edge.from, edge.to)
            );
            
            if (!isDirected) {
                if (seen.find(key) == seen.end()) {
                    edges.push_back(edge);
                    seen.insert(key);
                }
            } else {
                edges.push_back(edge);
            }
        }
    }
    return edges;
}

std::vector<Edge> Graph::getEdgesFrom(const std::string& nodeId) const {
    if (!hasNode(nodeId)) {
        return std::vector<Edge>();
    }
    return adjacencyList.at(nodeId);
}

std::vector<std::string> Graph::getNeighbors(const std::string& nodeId) const {
    std::vector<std::string> neighbors;
    if (hasNode(nodeId)) {
        for (const auto& edge : adjacencyList.at(nodeId)) {
            neighbors.push_back(edge.to);
        }
    }
    return neighbors;
}

Coordinates Graph::getNodePosition(const std::string& nodeId) const {
    if (nodePositions.find(nodeId) != nodePositions.end()) {
        return nodePositions.at(nodeId);
    }
    return Coordinates();
}

void Graph::clear() {
    adjacencyList.clear();
    nodePositions.clear();
    edgeCount = 0;
}

double Graph::getTotalWeight() const {
    double total = 0;
    for (const auto& edge : getEdges()) {
        total += edge.weight;
    }
    return total;
}

void Graph::printGraph() const {
    std::cout << "\n============ GRAPH ============" << std::endl;
    std::cout << "Nodes: " << getNodeCount() << ", Edges: " << getEdgeCount() << std::endl;
    std::cout << "Directed: " << (isDirected ? "Yes" : "No") << std::endl;
    std::cout << "\nAdjacency List:" << std::endl;
    
    for (const auto& pair : adjacencyList) {
        std::cout << "  " << pair.first << " -> ";
        if (pair.second.empty()) {
            std::cout << "(no edges)";
        } else {
            for (size_t i = 0; i < pair.second.size(); ++i) {
                std::cout << pair.second[i].to << "(" << pair.second[i].weight << ")";
                if (i < pair.second.size() - 1) std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "================================" << std::endl;
}

std::string Graph::toString() const {
    std::stringstream ss;
    ss << "Graph[Nodes=" << getNodeCount() << ", Edges=" << getEdgeCount() << "]";
    return ss.str();
}

Graph Graph::getSubgraph(const std::vector<std::string>& nodes) const {
    Graph subgraph(isDirected);
    
    for (const auto& node : nodes) {
        if (hasNode(node)) {
            subgraph.addNode(node, getNodePosition(node));
        }
    }
    
    for (const auto& node : nodes) {
        if (hasNode(node)) {
            for (const auto& edge : adjacencyList.at(node)) {
                if (subgraph.hasNode(edge.to)) {
                    subgraph.addEdge(edge);
                }
            }
        }
    }
    
    return subgraph;
}

} // namespace Algorithms
} // namespace HEROS