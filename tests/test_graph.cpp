#include "../include/algorithms/Graph.hpp"
#include "../include/algorithms/DijkstraRouter.hpp"
#include <iostream>
#include <cassert>

void testGraphConstruction() {
    std::cout << "\n🧪 Testing Graph Construction...\n";
    
    Graph g;
    g.addNode("A", Coordinates(0, 0));
    g.addNode("B", Coordinates(1, 0));
    g.addNode("C", Coordinates(1, 1));
    
    g.addBidirectionalEdge("A", "B", 10);
    g.addBidirectionalEdge("B", "C", 15);
    
    assert(g.getVertexCount() == 3);
    assert(g.hasNode("A"));
    assert(g.hasNode("B"));
    assert(!g.hasNode("D"));
    
    std::cout << "✓ Graph construction test passed!\n";
}

void testDijkstraAlgorithm() {
    std::cout << "\n🧪 Testing Dijkstra's Algorithm...\n";
    
    Graph g;
    g.addNode("A", Coordinates(0, 0));
    g.addNode("B", Coordinates(1, 0));
    g.addNode("C", Coordinates(2, 0));
    g.addNode("D", Coordinates(3, 0));
    
    g.addBidirectionalEdge("A", "B", 4);
    g.addBidirectionalEdge("A", "C", 2);
    g.addBidirectionalEdge("B", "C", 1);
    g.addBidirectionalEdge("B", "D", 5);
    g.addBidirectionalEdge("C", "D", 8);
    
    DijkstraRouter router(&g);
    RouteInfo route = router.findShortestPath("A", "D");
    
    assert(!route.path.empty());
    assert(route.path[0] == "A");
    assert(route.path[route.path.size() - 1] == "D");
    assert(route.totalDistance == 8); // A -> C -> B -> D
    
    std::cout << "✓ Dijkstra's algorithm test passed!\n";
}

int main() {
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║   GRAPH ALGORITHM UNIT TESTS         ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    
    testGraphConstruction();
    testDijkstraAlgorithm();
    
    std::cout << "\n✅ All Graph tests passed!\n\n";
    return 0;
}