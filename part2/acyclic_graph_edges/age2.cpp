#include <iostream>
#include <vector>
#include <set>

void dfs(int node, int parentEdgeIdx, std::vector<std::vector<std::pair<int, int>>>& adj, 
    std::vector<bool>& visited, std::vector<std::pair<int, int>>& result, std::set<int>& usedEdges)
{
    visited[node] = true;
    
    for (auto [neighbor, edgeIdx] : adj[node]) {
        if (edgeIdx == parentEdgeIdx) continue; // Don't go back on the same edge we came from
        
        if (usedEdges.find(edgeIdx) != usedEdges.end()) continue; // Already oriented this edge
        
        if (!visited[neighbor]) {
            result.push_back({node, neighbor});
            usedEdges.insert(edgeIdx);
            dfs(neighbor, edgeIdx, adj, visited, result, usedEdges);
        } else {
            // Back edge. Orient from visited to current to avoid cycle
            result.push_back({neighbor, node});
            usedEdges.insert(edgeIdx);
        }
    }
}

int main() {
    int nodeCount, edgeCount;
    std::cin >> nodeCount >> edgeCount;

    std::vector<std::vector<std::pair<int, int>>> adj(nodeCount);

    for (int i = 0; i < edgeCount; i++) {
        int a, b;
        std::cin >> a >> b;
        a--; b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    std::vector<bool> visited(nodeCount, false);
    std::vector<std::pair<int, int>> result;
    std::set<int> usedEdges;

    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i]) {
            dfs(i, -1, adj, visited, result, usedEdges);
        }
    }

    for (auto edgePair : result) {
        std::cout << edgePair.first + 1 << " " << edgePair.second + 1 << "\n";
    }
}
