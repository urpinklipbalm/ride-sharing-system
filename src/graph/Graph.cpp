#include "Graph.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

void Graph::addEdge(int u, int v, double weight) {
    adjList[u].emplace_back(v, weight);
    adjList[v].emplace_back(u, weight); // Assuming undirected graph
}

std::vector<int> Graph::dijkstra(int start, int goal) {
    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    for (const auto& pair : adjList) {
        dist[pair.first] = std::numeric_limits<double>::infinity();
    }
    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == goal) break;

        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            double weight = neighbor.second;
            double alt = dist[u] + weight;

            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.emplace(alt, v);
            }
        }
    }

    std::vector<int> path;
    for (int at = goal; at != start; at = prev[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}