// include/algorithms/MSTGenerator.hpp
#ifndef MST_GENERATOR_HPP
#define MST_GENERATOR_HPP

#include "Graph.hpp"

namespace HEROS {
namespace Algorithms {

/**
 * MSTGenerator - Minimum Spanning Tree using Kruskal's Algorithm
 * 
 * Time Complexity: O(E log E) with Union-Find (path compression + union by rank)
 * Space Complexity: O(V)
 * 
 * Used for optimizing equipment distribution (oxygen lines, cables, etc.)
 */
class MSTGenerator {
private:
    Graph sourceGraph;
    
    // Union-Find (Disjoint Set Union) data structure
    class UnionFind {
    private:
        std::unordered_map<std::string, std::string> parent;
        std::unordered_map<std::string, int> rank;
        
    public:
        void makeSet(const std::string& node);
        std::string find(const std::string& node);
        bool unite(const std::string& node1, const std::string& node2);
        bool connected(const std::string& node1, const std::string& node2);
    };
    
    PerformanceMetrics lastMetrics;

public:
    // Constructors
    MSTGenerator();
    MSTGenerator(const Graph& graph);
    
    // Destructor
    ~MSTGenerator() = default;
    
    // Set source graph
    void setGraph(const Graph& graph) { sourceGraph = graph; }
    Graph getSourceGraph() const { return sourceGraph; }
    
    // Generate MST
    Graph generateMST();
    
    // Cost analysis
    double getMSTCost(const Graph& mst) const;
    double getCostReduction() const; // Percentage saved vs original
    
    // Utility
    void printMST(const Graph& mst) const;
    bool isMSTValid(const Graph& mst) const;
    
    // Performance metrics
    PerformanceMetrics getLastOperationMetrics() const { return lastMetrics; }
};

} // namespace Algorithms
} // namespace HEROS

#endif // MST_GENERATOR_HPP