#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <climits>

class Graph {
private:
    int vertices;
    std::vector<std::vector<int> > adjMatrix;
    std::vector<std::vector<int> > adjList;
    std::vector<char> vertexNames;

public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(vertices, std::vector<int>(vertices, 0));
        adjList.resize(vertices);
        vertexNames.resize(vertices);
    }

    void setVertexName(int index, char name) {
        vertexNames[index] = name;
    }

    char getVertexName(int index) {
        return vertexNames[index];
    }

    int getVertexIndex(char name) {
        for (int i = 0; i < vertices; i++) {
            if (vertexNames[i] == name) {
                return i;
            }
        }
        return -1;
    }

    void addEdge(int u, int v, int weight = 1) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printAdjMatrix() {
        std::cout << "Adjacency Matrix:" << std::endl;
        std::cout << "  ";
        for (int i = 0; i < vertices; i++) {
            std::cout << vertexNames[i] << " ";
        }
        std::cout << std::endl;
        
        for (int i = 0; i < vertices; i++) {
            std::cout << vertexNames[i] << " ";
            for (int j = 0; j < vertices; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void BFS(int start) {
        std::vector<bool> visited(vertices, false);
        std::queue<int> q;
        
        std::cout << "BFS from " << vertexNames[start] << ": ";
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            std::cout << vertexNames[current] << " ";
            
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        std::cout << std::endl;
    }

    void DFSUtil(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << vertexNames[v] << " ";
        
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[v][i] != 0 && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS(int start) {
        std::vector<bool> visited(vertices, false);
        std::cout << "DFS from " << vertexNames[start] << ": ";
        DFSUtil(start, visited);
        std::cout << std::endl;
    }

    void dijkstra(int start) {
        std::vector<int> dist(vertices, INT_MAX);
        std::vector<bool> visited(vertices, false);
        std::vector<int> parent(vertices, -1);
        
        dist[start] = 0;
        
        for (int count = 0; count < vertices - 1; count++) {
            int u = -1;
            for (int i = 0; i < vertices; i++) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }
            
            if (dist[u] == INT_MAX) break;
            
            visited[u] = true;
            
            for (int v = 0; v < vertices; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDist = dist[u] + adjMatrix[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        parent[v] = u;
                    }
                }
            }
        }
        
        std::cout << "Shortest paths from " << vertexNames[start] << ":" << std::endl;
        for (int i = 0; i < vertices; i++) {
            if (i != start) {
                std::cout << "To " << vertexNames[i] << ": " << dist[i] << " ";
                if (dist[i] != INT_MAX) {
                    std::cout << "Path: ";
                    std::vector<char> path;
                    for (int j = i; j != -1; j = parent[j]) {
                        path.push_back(vertexNames[j]);
                    }
                    for (int j = path.size() - 1; j >= 0; j--) {
                        std::cout << path[j];
                        if (j > 0) std::cout << "->";
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    void primMST() {
        std::vector<int> key(vertices, INT_MAX);
        std::vector<bool> inMST(vertices, false);
        std::vector<int> parent(vertices, -1);
        
        key[0] = 0;
        
        for (int count = 0; count < vertices - 1; count++) {
            int u = -1;
            for (int i = 0; i < vertices; i++) {
                if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                    u = i;
                }
            }
            
            inMST[u] = true;
            
            for (int v = 0; v < vertices; v++) {
                if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }
        
        std::cout << "Minimum Spanning Tree (Prim):" << std::endl;
        int totalWeight = 0;
        for (int i = 1; i < vertices; i++) {
            if (parent[i] != -1) {
                std::cout << vertexNames[parent[i]] << " - " << vertexNames[i] 
                         << " : " << adjMatrix[i][parent[i]] << std::endl;
                totalWeight += adjMatrix[i][parent[i]];
            }
        }
        std::cout << "Total weight: " << totalWeight << std::endl;
    }

    void bridgeDFS(int u, std::vector<bool>& visited, std::vector<int>& disc, 
                  std::vector<int>& low, std::vector<int>& parent, 
                  std::vector<std::pair<int, int> >& bridges,
                  std::vector<bool>& isArticulation, std::vector<int>& children, int& time) {
        visited[u] = true;
        disc[u] = low[u] = ++time;
        
        for (std::vector<int>::iterator it = adjList[u].begin(); it != adjList[u].end(); ++it) {
            int v = *it;
            
            if (!visited[v]) {
                children[u]++;
                parent[v] = u;
                bridgeDFS(v, visited, disc, low, parent, bridges, isArticulation, children, time);
                
                low[u] = std::min(low[u], low[v]);
                
                // 桥的条件
                if (low[v] > disc[u]) {
                    bridges.push_back(std::make_pair(u, v));
                }
                
                // 关节点的条件
                if (parent[u] == -1 && children[u] > 1) {
                    isArticulation[u] = true;
                }
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    isArticulation[u] = true;
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }
    }

    void findBridgesAndArticulationPoints(int start) {
        std::vector<bool> visited(vertices, false);
        std::vector<int> disc(vertices, -1);
        std::vector<int> low(vertices, -1);
        std::vector<int> parent(vertices, -1);
        std::vector<std::pair<int, int> > bridges;
        std::vector<bool> isArticulation(vertices, false);
        std::vector<int> children(vertices, 0);
        
        std::cout << "Starting from vertex " << vertexNames[start] << ":" << std::endl;
        
        int time = 0;
        
        // 从指定起点开始DFS
        if (!visited[start]) {
            bridgeDFS(start, visited, disc, low, parent, bridges, isArticulation, children, time);
        }
        
        // 继续遍历其他未访问的连通分量
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                bridgeDFS(i, visited, disc, low, parent, bridges, isArticulation, children, time);
            }
        }
        
        std::cout << "Bridges: ";
        if (bridges.empty()) {
            std::cout << "None";
        } else {
            for (size_t i = 0; i < bridges.size(); i++) {
                std::cout << vertexNames[bridges[i].first] << "-" 
                         << vertexNames[bridges[i].second];
                if (i < bridges.size() - 1) std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        std::cout << "Articulation points: ";
        bool found = false;
        for (int i = 0; i < vertices; i++) {
            if (isArticulation[i]) {
                std::cout << vertexNames[i] << " ";
                found = true;
            }
        }
        if (!found) std::cout << "None";
        std::cout << std::endl;
    }
};

#endif
