#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <limits>
#include <iostream>

namespace Algorithms {

    /**
     * Edge Structure
     * Represents a weighted edge between two nodes
     */
    struct Edge {
        std::string source;
        std::string destination;
        double weight;
        bool bidirectional;

        Edge() : weight(0), bidirectional(true) {}
        Edge(const std::string& src, const std::string& dest, double w, bool bidir = true)
            : source(src), destination(dest), weight(w), bidirectional(bidir) {}

        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }

        bool operator>(const Edge& other) const {
            return weight > other.weight;
        }

        bool operator==(const Edge& other) const {
            return source == other.source && destination == other.destination;
        }
    };

    /**
     * Node Position Structure
     */
    struct NodePosition {
        double x;
        double y;
        int floor;

        NodePosition() : x(0), y(0), floor(0) {}
        NodePosition(double x, double y, int f = 0) : x(x), y(y), floor(f) {}

        double distanceTo(const NodePosition& other) const {
            double dx = x - other.x;
            double dy = y - other.y;
            double df = (floor - other.floor) * 10.0;  // Floor difference has higher weight
            return std::sqrt(dx*dx + dy*dy + df*df);
        }
    };

    /**
     * Graph Class
     * 
     * Adjacency list representation of hospital layout.
     * Supports both directed and undirected graphs.
     * 
     * Used for:
     * - Hospital room connectivity
     * - Staff routing
     * - Equipment distribution paths
     */
    class Graph {
    private:
        std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
        std::unordered_map<std::string, NodePosition> nodePositions;
        std::set<std::string> nodes;
        int edgeCount;
        bool isDirected;

    public:
        // Constructors
        Graph(bool directed = false);
        Graph(const Graph& other);
        
        // Destructor
        ~Graph();

        // Assignment operator
        Graph& operator=(const Graph& other);

        // Node Operations
        void addNode(const std::string& nodeId);
        void addNode(const std::string& nodeId, const NodePosition& position);
        void removeNode(const std::string& nodeId);
        bool hasNode(const std::string& nodeId) const;
        NodePosition getNodePosition(const std::string& nodeId) const;
        void setNodePosition(const std::string& nodeId, const NodePosition& position);

        // Edge Operations
        void addEdge(const std::string& from, const std::string& to, double weight);
        void addEdge(const Edge& edge);
        void removeEdge(const std::string& from, const std::string& to);
        bool hasEdge(const std::string& from, const std::string& to) const;
        double getEdgeWeight(const std::string& from, const std::string& to) const;
        void updateEdgeWeight(const std::string& from, const std::string& to, double newWeight);

        // Graph Properties
        int getNodeCount() const { return nodes.size(); }
        int getEdgeCount() const { return edgeCount; }
        bool isDirectedGraph() const { return isDirected; }
        bool isEmpty() const { return nodes.empty(); }
        
        // Retrieval Operations
        std::vector<std::string> getNodes() const;
        std::vector<Edge> getEdges() const;
        std::vector<Edge> getAdjacentEdges(const std::string& nodeId) const;
        std::vector<std::string> getNeighbors(const std::string& nodeId) const;
        
        // Graph Algorithms Helpers
        std::unordered_map<std::string, std::vector<Edge>>& getAdjacencyList() { 
            return adjacencyList; 
        }
        const std::unordered_map<std::string, std::vector<Edge>>& getAdjacencyList() const { 
            return adjacencyList; 
        }

        // Utility Methods
        void clear();
        void display() const;
        std::string toString() const;

        // Graph Validation
        bool isConnected() const;
        bool hasCycle() const;

        // Static Constants
        static const double INFINITY_WEIGHT;
    };

    const double Graph::INFINITY_WEIGHT = std::numeric_limits<double>::infinity();

} // namespace Algorithms

#endif // GRAPH_HPP