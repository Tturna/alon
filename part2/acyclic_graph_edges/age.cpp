/*
Given an undirected graph, your task is to choose a direction for each edge so that the
resulting directed graph is acyclic.

Input

The first input line has two integers n and m: the number of nodes and edges.
The nodes are numbered 1,2,...,n. After this, there are m lines describing the edges.
Each line has two distinct integers a and b: there is an edge between nodes a and b.

Output

Print m lines describing the directions of the edges. Each line has two integers a and
b: there is an edge from node a to node b. You can print any valid solution.

Constraints

1 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n

Example
Input:
3 3
1 2
2 3
3 1

Output:
1 2
3 2
3 1
*/

#include <iostream>
#include <unordered_set>
#include <vector>

void makeDirectedEdges(int currentNode, int parent, std::vector<std::vector<int>>& adj,
    std::vector<int>& visited, std::vector<std::unordered_multiset<int>>& newEdges)
{
    if (visited[currentNode] > -1) {
        return;
    }

    // std::cout << "handling " << currentNode + 1 << "\n";

    for (auto neighbor : adj[currentNode]) {
        if (neighbor == parent) continue;

        if (visited[neighbor] > -1 && visited[neighbor] != currentNode) {
            if (newEdges[currentNode].find(neighbor) == newEdges[currentNode].end()) {
                // std::cout << "visited. adding " << neighbor + 1 << " " << currentNode + 1 << "\n"; 
                newEdges[neighbor].insert(currentNode);
            }

            continue;
        }
        else {
            visited[neighbor] = currentNode;
        }

        // std::cout << "adding " << currentNode + 1 << " " << neighbor + 1 << "\n";
        newEdges[currentNode].insert(neighbor);
        makeDirectedEdges(neighbor, currentNode, adj, visited, newEdges);
    }
}

int main() {
    int nodeCount, edgeCount;
    std::cin >> nodeCount >> edgeCount;

    std::vector<std::vector<int>> ogEdges(nodeCount);

    for (int i = 0; i < edgeCount; i++) {
        int a, b;
        std::cin >> a >> b;
        ogEdges[a - 1].push_back(b - 1);
        ogEdges[b - 1].push_back(a - 1);
    }

    std::vector<int> visited(nodeCount, -1);
    std::vector<std::unordered_multiset<int>> newEdges(nodeCount);

    for (int i = 0; i < nodeCount; i++) {
        makeDirectedEdges(i, -1, ogEdges, visited, newEdges);
    }

    // std::cout << "new edges:\n";

    for (int i = 0; i < nodeCount; i++) {
        if (newEdges[i].empty()) continue;

        for (auto neighbor : newEdges[i]) {
            std::cout << i + 1 << " " << neighbor + 1 << "\n";
        }
    }
}
