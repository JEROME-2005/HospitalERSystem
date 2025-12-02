#ifndef MST_GENERATOR_HPP
#define MST_GENERATOR_HPP

#include "Graph.hpp"
#include <vector>
#include <string>
#include <map>

namespace Algorithms {

    /**
     * Union-Find (Disjoint Set Union) Class
     * 
     * Used by Kruskal's algorithm for cycle detection.
     * Implements path compression and union by rank for optimal performance.
     * 
     * Time Complexity (with optimizations):
     * - find(): O(α(n)) ≈ O(1) amortized
     * - union(): O(α(n)) ≈ O(1) amortized
     * 
     * α(n) is the inverse Ackermann function, which grows very slowly.
     */
    class UnionFind {
    private:
        std::map<std::string, std::string> parent;
        std::map<std::string, int> rank;

    public:
        UnionFind();
        UnionFind(const std::vector<std::string>& elements);
        
        void makeSet(const std::string& element);
        std::string find(const std::string& element);
        bool unionSets(const std::string& x, const std::string& y);
        bool connected(const std::string& x, const std::string& y);
        void reset();
    };

    /**
     * MST Result Structure
     */
    struct MSTResult {
        Graph mstGraph;
        double totalWeight;
        int edgesInMST;
        std::vector<Edge> mstEdges;
        double computationTimeMs;
        bool isComplete;  // True if MST spans all nodes

        MSTResult() : totalWeight(0), edgesInMST(0), computationTimeMs(0), isComplete(false) {}
    };

    /**
     * MSTGenerator Class
     * 
     * Generates Minimum Spanning Tree using Kruskal's algorithm.
     * 
     * Use Cases:
     * - Minimize total cable length for oxygen lines across ICU rooms
     * - Optimize emergency communication network setup
     * - Efficient equipment distribution pathways
     * 
     * Time Complexity: O(E log E) where E is number of edges
     *   - Dominated by sorting edges
     *   - Union-Find operations are nearly O(1) with optimizations
     * 
     * Space Complexity: O(V + E)
     */
    class MSTGenerator {
    private:
        Graph* sourceGraph;
        UnionFind disjointSet;
        
        // Performance Metrics
        int edgesConsidered;
        double lastComputationTime;
        double originalGraphWeight;

    public:
        // Constructors
        MSTGenerator();
        MSTGenerator(Graph* graph);
        MSTGenerator(const MSTGenerator& other);
        
        // Destructor
        ~MSTGenerator();

        // Assignment operator
        MSTGenerator& operator=(const MSTGenerator& other);

        // Graph Management
        void setGraph(Graph* graph) { sourceGraph = graph; }
        Graph* getGraph() const { return sourceGraph; }

        // Core MST Operations - Kruskal's Algorithm
        MSTResult generateMinimumSpanningTree();
        
        // Alternative: Prim's Algorithm (for comparison)
        MSTResult generateMSTPrims(const std::string& startNode);

        // Analysis Methods
        double calculateCostSavings() const;  // MST weight vs original graph weight
        double getSavingsPercentage() const;
        
        // Specific Use Cases
        MSTResult generateOxygenLineNetwork(const std::vector<std::string>& icuRooms);
        MSTResult generateEmergencyCommNetwork(const std::vector<std::string>& criticalRooms);

        // Performance Metrics
        int getEdgesConsidered() const { return edgesConsidered; }
        double getLastComputationTime() const { return lastComputationTime; }
        double getOriginalGraphWeight() const { return originalGraphWeight; }
        
        // Utility Methods
        void reset();
        std::string getComplexityAnalysis() const;
        void displayMST(const MSTResult& result) const;

    private:
        // Helper Methods
        std::vector<Edge> getSortedEdges();
        double calculateTotalGraphWeight();
    };

} // namespace Algorithms

#endif // MST_GENERATOR_HPP