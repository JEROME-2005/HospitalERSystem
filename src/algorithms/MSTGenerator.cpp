// src/algorithms/MSTGenerator.cpp
#include "../../include/algorithms/MSTGenerator.hpp"

namespace HEROS {
namespace Algorithms {

// ============== UnionFind Implementation ==============

void MSTGenerator::UnionFind::makeSet(const std::string& node) {
    if (parent.find(node) == parent.end()) {
        parent[node] = node;
        rank[node] = 0;
    }
}

std::string MSTGenerator::UnionFind::find(const std::string& node) {
    if (parent.find(node) == parent.end()) {
        makeSet(node);
    }
    
    // Path compression
    if (parent[node] != node) {
        parent[node] = find(parent[node]);
    }
    return parent[node];
}

bool MSTGenerator::UnionFind::unite(const std::string& node1, const std::string& node2) {
    std::string root1 = find(node1);
    std::string root2 = find(node2);
    
    if (root1 == root2) {
        return false; // Already in same set
    }
    
    // Union by rank
    if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    } else if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    } else {
        parent[root2] = root1;
        rank[root1]++;
    }
    
    return true;
}

bool MSTGenerator::UnionFind::connected(const std::string& node1, const std::string& node2) {
    return find(node1) == find(node2);
}

// ============== MSTGenerator Implementation ==============

MSTGenerator::MSTGenerator() : sourceGraph(false) {}

MSTGenerator::MSTGenerator(const Graph& graph) : sourceGraph(graph) {}

Graph MSTGenerator::generateMST() {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    Graph mst(false); // MST is always undirected
    UnionFind uf;
    
    // Get all edges and sort by weight
    std::vector<Edge> edges = sourceGraph.getEdges();
    std::sort(edges.begin(), edges.end()); // Uses operator< for Edge
    
    // Add all nodes to MST and UnionFind
    for (const auto& node : sourceGraph.getNodes()) {
        mst.addNode(node, sourceGraph.getNodePosition(node));
        uf.makeSet(node);
    }
    
    int edgesAdded = 0;
    int nodesCount = sourceGraph.getNodeCount();
    size_t operationsCount = 0;
    
    // Kruskal's algorithm: add edges in order of weight
    for (const auto& edge : edges) {
        operationsCount++;
        
        // If adding this edge doesn't create a cycle
        if (!uf.connected(edge.from, edge.to)) {
            mst.addEdge(edge.from, edge.to, edge.weight);
            uf.unite(edge.from, edge.to);
            edgesAdded++;
            
            // MST has V-1 edges
            if (edgesAdded >= nodesCount - 1) {
                break;
            }
        }
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    // Record metrics
    lastMetrics.algorithmName = "Kruskal's MST";
    lastMetrics.complexity = "O(E log E)";
    lastMetrics.executionTimeMs = std::chrono::duration<double, std::milli>(
        endTime - startTime).count();
    lastMetrics.operationsCount = operationsCount;
    
    return mst;
}

double MSTGenerator::getMSTCost(const Graph& mst) const {
    return mst.getTotalWeight();
}

double MSTGenerator::getCostReduction() const {
    double originalCost = sourceGraph.getTotalWeight();
    Graph mst = const_cast<MSTGenerator*>(this)->generateMST();
    double mstCost = getMSTCost(mst);
    
    if (originalCost == 0) return 0;
    
    return ((originalCost - mstCost) / originalCost) * 100.0;
}

void MSTGenerator::printMST(const Graph& mst) const {
    std::cout << "\n============ MINIMUM SPANNING TREE ============" << std::endl;
    std::cout << "Nodes: " << mst.getNodeCount() << std::endl;
    std::cout << "Edges: " << mst.getEdgeCount() << std::endl;
    std::cout << "Total Cost: " << getMSTCost(mst) << std::endl;
    std::cout << "\nEdges in MST:" << std::endl;
    
    for (const auto& edge : mst.getEdges()) {
        std::cout << "  " << edge.from << " -- " << edge.to 
                  << " (weight: " << edge.weight << ")" << std::endl;
    }
    std::cout << "================================================" << std::endl;
}

bool MSTGenerator::isMSTValid(const Graph& mst) const {
    // Check if MST has V-1 edges for V nodes
    return mst.getEdgeCount() == mst.getNodeCount() - 1;
}

} // namespace Algorithms
} // namespace HEROS