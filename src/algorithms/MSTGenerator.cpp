#include "../../include/algorithms/MSTGenerator.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>

// UnionFind Implementation
void UnionFind::makeSet(const std::string& node) {
    parent[node] = node;
    rank[node] = 0;
}

std::string UnionFind::find(const std::string& node) {
    if (parent[node] != node) {
        parent[node] = find(parent[node]); // Path compression
    }
    return parent[node];
}

bool UnionFind::unionSets(const std::string& node1, const std::string& node2) {
    std::string root1 = find(node1);
    std::string root2 = find(node2);
    
    if (root1 == root2) return false; // Already in same set
    
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

// MSTGenerator Implementation
MSTGenerator::MSTGenerator(Graph* graph) : equipmentGraph(graph) {}

MSTResult MSTGenerator::generateMinimumSpanningTree() {
    MSTResult result;
    
    // Get all edges and sort by weight - O(E log E)
    std::vector<Edge> allEdges = equipmentGraph->getAllEdges();
    std::sort(allEdges.begin(), allEdges.end());
    
    // Initialize Union-Find
    UnionFind uf;
    for (const std::string& node : equipmentGraph->getAllNodes()) {
        uf.makeSet(node);
    }
    
    // Kruskal's Algorithm
    for (const Edge& edge : allEdges) {
        if (uf.unionSets(edge.from, edge.to)) {
            result.edges.push_back(edge);
            result.totalWeight += edge.weight;
            result.edgeCount++;
            
            // MST has V-1 edges
            if (result.edgeCount == equipmentGraph->getVertexCount() - 1) {
                break;
            }
        }
    }
    
    return result;
}

double MSTGenerator::calculateOptimizationPercentage(const MSTResult& mst) const {
    // Calculate total weight if all nodes were connected to a central point
    std::vector<Edge> allEdges = equipmentGraph->getAllEdges();
    double totalPossibleWeight = 0.0;
    
    for (const Edge& edge : allEdges) {
        totalPossibleWeight += edge.weight;
    }
    
    double savings = ((totalPossibleWeight - mst.totalWeight) / totalPossibleWeight) * 100.0;
    return savings;
}

void MSTGenerator::displayMST(const MSTResult& mst) const {
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║       MINIMUM SPANNING TREE (MST)              ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    std::cout << "║ Total Cable Length: " << std::setw(26) << std::fixed 
              << std::setprecision(2) << mst.totalWeight << "m ║\n";
    std::cout << "║ Number of Connections: " << std::setw(23) << mst.edgeCount << " ║\n";
    std::cout << "║ Optimization: " << std::setw(30) << std::fixed 
              << std::setprecision(1) << calculateOptimizationPercentage(mst) << "% ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    
    std::cout << "\nMST Edges:\n";
    for (const Edge& edge : mst.edges) {
        std::cout << "  " << edge.from << " ↔ " << edge.to 
                  << " : " << std::fixed << std::setprecision(2) 
                  << edge.weight << "m\n";
    }
}