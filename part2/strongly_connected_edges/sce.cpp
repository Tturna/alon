/*
Given an undirected graph, your task is to choose a direction for each edge so that
the resulting directed graph is strongly connected.

Input

The first input line has two integers n and m: the number of nodes and edges. The nodes
are numbered 1,2,...,n. After this, there are m lines describing the edges. Each line has
two integers a and b: there is an edge between nodes a and b. You may assume that the graph
is simple, i.e., there are at most one edge between two nodes and every edge connects two
distinct nodes.

Output

Print m lines describing the directions of the edges. Each line has two integers a and b:
there is an edge from node a to node b. You can print any valid solution.
If there are no solutions, only print IMPOSSIBLE.

Constraints

1 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n

Example
Input:
3 3
1 2
1 3
2 3

Output:
1 2
2 3
3 1
*/

#include <iostream>
#include <limits>
#include <set>
#include <utility>
#include <vector>

struct node {
    int discoveryDepth;
    int minReachableDepth;

    node() {
        this->discoveryDepth = 0;
        this->minReachableDepth = std::numeric_limits<int>::max();
    }
};

void getTreeEdgesDfs(int currentNode, int previousNode, std::vector<bool>& visited,
    std::vector<std::vector<std::pair<int, int>>>& adjacencyTable, int& depth,
    std::vector<node>& nodes, std::vector<std::pair<int, int>>& treeEdges)
{
    if (visited[currentNode]) {
        return;
    }

    visited[currentNode] = true;
    nodes[currentNode].discoveryDepth = depth;
    nodes[currentNode].minReachableDepth = depth;
    depth++;

    for (auto [neighbor, edgeIndex] : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        bool isNeighborVisited = visited[neighbor];

        if (!isNeighborVisited) {
            treeEdges.push_back({currentNode, neighbor});
        }

        getTreeEdgesDfs(neighbor, currentNode, visited, adjacencyTable, depth, nodes, treeEdges);

        if (isNeighborVisited) {
            nodes[currentNode].minReachableDepth = std::min(nodes[currentNode].minReachableDepth,
                nodes[neighbor].discoveryDepth);
        }
        else {
            nodes[currentNode].minReachableDepth = std::min(nodes[currentNode].minReachableDepth,
                nodes[neighbor].minReachableDepth);
        }
    }
}

void makeDirectedEdgesDfs(int currentNode, int parent, std::vector<std::vector<std::pair<int, int>>>& adj,
    std::vector<bool>& visited, std::vector<std::pair<int, int>>& newEdges,
    std::set<int>& usedEdges, bool& impossible)
{
    if (visited[currentNode]) return;

    visited[currentNode] = true;

    if (adj[currentNode].size() <= 1) {
        impossible = true;
        return;
    }

    for (auto [neighbor, edgeIndex] : adj[currentNode]) {
        if (neighbor == parent) continue;
        if (usedEdges.find(edgeIndex) != usedEdges.end()) continue;

        newEdges.push_back({currentNode, neighbor});
        usedEdges.insert(edgeIndex);

        if (!visited[neighbor]) {
            makeDirectedEdgesDfs(neighbor, currentNode, adj, visited, newEdges, usedEdges, impossible);
            if (impossible) return;
        }
    }
}

int main() {
    int nodeCount, edgeCount;
    std::cin >> nodeCount >> edgeCount;

    std::vector<std::vector<std::pair<int, int>>> adj(nodeCount);

    for (int i = 0; i < edgeCount; i++) {
        int from, to;
        std::cin >> from >> to;
        from--; to--;
        adj[from].push_back({to, i});
        adj[to].push_back({from, i});
    }

    std::vector<bool> visited(nodeCount, false);
    std::vector<node> nodes(nodeCount);
    std::vector<std::pair<int, int>> treeEdges;
    int depth = 0;
    getTreeEdgesDfs(0, 0, visited, adj, depth, nodes, treeEdges);

    for (auto edge : treeEdges) {
        int from = edge.first;
        int to = edge.second;

        if (nodes[to].minReachableDepth > nodes[from].discoveryDepth) {
            // bridge exists -> can't make a single strongly connected component
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    visited.clear();
    visited = std::vector<bool>(nodeCount, false);
    std::set<int> usedEdges;
    std::vector<std::pair<int, int>> newEdges;
    bool impossible = false;
    makeDirectedEdgesDfs(0, -1, adj, visited, newEdges, usedEdges, impossible);

    if (impossible) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i]) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // std::cout << "new edges:\n";

    for (auto [a, b] : newEdges) {
        std::cout << a + 1 << " " << b + 1 << "\n";
    }
}
