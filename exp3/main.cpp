#include "Graph.h"
#include <iostream>
void buildGraph1(Graph& g) {
    // 给结点命名 
    g.setVertexName(0, 'A');
    g.setVertexName(1, 'B');
    g.setVertexName(2, 'C');
    g.setVertexName(3, 'D');
    g.setVertexName(4, 'E');
    g.setVertexName(5, 'F');
    g.setVertexName(6, 'G');    
    // 添加边
    g.addEdge(0, 1, 6);  // A-B:6
    g.addEdge(0, 3, 2);  // A-D:2
    g.addEdge(0, 6, 4);  // A-G:4
    g.addEdge(1, 2, 9);  // B-C:9
    g.addEdge(1, 4, 13); // B-E:13
    g.addEdge(2, 4, 11); // C-E:11
    g.addEdge(2, 5, 2);  // C-F:2
    g.addEdge(3, 4, 14); // D-E:14
    g.addEdge(4, 5, 1);  // E-F:1
    g.addEdge(4, 6, 5);  // E-G:5
    g.addEdge(5, 6, 8);  // F-G:8
}
void buildGraph2(Graph& g) {
    // 给顶点命名 
    g.setVertexName(0, 'A');
    g.setVertexName(1, 'B');
    g.setVertexName(2, 'C');
    g.setVertexName(3, 'D');
    g.setVertexName(4, 'E');
    g.setVertexName(5, 'F');
    g.setVertexName(6, 'G');
    g.setVertexName(7, 'H');
    g.setVertexName(8, 'I');
    g.setVertexName(9, 'J');
    g.setVertexName(10, 'K');
    g.setVertexName(11, 'L');
    // 添加边
    g.addEdge(0, 1, 4);   // A-B:4
    g.addEdge(0, 2, 13);  // A-C:13
    g.addEdge(0, 3, 11);  // A-D:11
    g.addEdge(1, 4, 12);  // B-E:12
    g.addEdge(1, 5, 1);   // B-F:1
    g.addEdge(2, 5, 5);   // C-F:5
    g.addEdge(2, 6, 8);   // C-G:8
    g.addEdge(3, 6, 7);   // D-G:7
    g.addEdge(3, 7, 3);   // D-H:3
    g.addEdge(4, 8, 9);   // E-I:9
    g.addEdge(5, 8, 6);   // F-I:6
    g.addEdge(5, 9, 2);   // F-J:2
    g.addEdge(6, 9, 10);  // G-J:10
    g.addEdge(6, 10, 15); // G-K:15
    g.addEdge(7, 10, 16); // H-K:16
    g.addEdge(8, 11, 17); // I-L:17
    g.addEdge(9, 11, 18); // J-L:18
    g.addEdge(10, 11, 19); // K-L:19
}
int main() {
    std::cout << "=== Graph 1 ===" << std::endl;
    Graph g1(7);
    buildGraph1(g1);
    g1.printAdjMatrix();
    std::cout << std::endl;
    g1.BFS(0); 
    g1.DFS(0); 
    std::cout << std::endl;
    g1.dijkstra(0); 
    std::cout << std::endl;
    g1.primMST();   
    std::cout << std::endl;
    std::cout << "=== Graph 2 ===" << std::endl;
    Graph g2(12);
    buildGraph2(g2);
    std::cout << "Biconnected Components Analysis:" << std::endl;
    g2.findBridgesAndArticulationPoints(0); 
    std::cout << std::endl;
    g2.findBridgesAndArticulationPoints(5);  
    std::cout << std::endl;
    g2.findBridgesAndArticulationPoints(8);  
    return 0;
}
