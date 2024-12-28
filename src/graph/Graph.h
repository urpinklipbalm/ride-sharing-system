// filepath: /Users/asma/Desktop/📎/nust/sophmore/data structure + algorithms/project/ride-sharing-system/src/graph/Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <limits>
#include <queue>
#include <utility>

class Graph {
public:
    void addEdge(int u, int v, double weight);
    std::vector<int> dijkstra(int start, int goal);

private:
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjList;
};

#endif // GRAPH_H