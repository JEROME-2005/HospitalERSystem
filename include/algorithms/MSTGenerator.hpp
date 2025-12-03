#ifndef MST_GENERATOR_HPP
#define MST_GENERATOR_HPP

#include "Graph.hpp"
#include <vector>
#include <unordered_map>

struct MSTResult {
    std::vector<Edge> edges;
    double totalWeight;
    int edgeCount;
    
    MSTResult() : totalWeight(0.0), edgeCount(0) {}
};

// Union-Find data structure for Kruskal's algorithm
class UnionFind {
private:
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, int> rank;

public:
    void makeSet(const std::string& node);
    std::string find(const std::string& node);           // With path compression
    bool unionSets(const std::string& node1, const std::string& node2);  // With union by rank
};

class MSTGenerator {
private:
    Graph* equipmentGraph;

public:
    MSTGenerator(Graph* graph);
    
    // Kruskal's Algorithm - O(E log E) complexity
    MSTResult generateMinimumSpanningTree();
    
    // Calculate savings compared to naive approach
    double calculateOptimizationPercentage(const MSTResult& mst) const;
    
    // Utility
    void displayMST(const MSTResult& mst) const;
};

#endif // MST_GENERATOR_HPP