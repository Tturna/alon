/*
A directed acyclic graph consists of n nodes and m edges. The nodes are numbered 1,2,...,n.
Calculate for each node the number of nodes you can reach from that node (including the node
itself).

Input

The first input line has two integers n and m: the number of nodes and edges.
Then there are m lines describing the edges. Each line has two distinct integers a and b: there
is an edge from node a to node b.

Output

Print n integers: for each node the number of reachable nodes.

Constraints

1 <= n <= 5 * 10^4
1 <= m <= 10^5

Example
Input:
5 6
1 2
1 3
1 4
2 3
3 5
4 5

Output:
5 3 2 2 1
*/

#include <bitset>
#include <iostream>
#include <vector>

void reverseToposort(int node, std::vector<bool>& visited, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<int>& topoList) {
    if (visited[node]) {
        return;
    }

    visited[node] = true;

    for (auto neighbor : adjacencyTable[node]) {
        reverseToposort(neighbor, visited, adjacencyTable, topoList);
    }

    topoList.push_back(node);
}

int main() {
    const int MAX_NODES = 50000;

    int nodeCount;
    int edgeCount;

    std::cin >> nodeCount;
    std::cin >> edgeCount;

    std::vector<std::vector<int>> adjacencyTable(nodeCount);

    for (int i = 0; i < edgeCount; i++) {
        int from;
        int to;
        std::cin >> from >> to;
        adjacencyTable[from - 1].push_back(to - 1);
    }

    std::vector<bool> visited(nodeCount, false);
    std::vector<int> topoList;

    for (int i = 0; i < nodeCount; i++) {
        reverseToposort(i, visited, adjacencyTable, topoList);
    }

    std::vector<std::bitset<MAX_NODES>> reachables(nodeCount);
    reachables[topoList[0]].set(topoList[0]);

    for (int i = 1; i < nodeCount; i++) {
        int next = topoList[i];
        reachables[next].set(next);

        for (int neighbor : adjacencyTable[next]) {
            reachables[next] |= reachables[neighbor];
        }
    }

    for (int i = 0; i < nodeCount; i++) {
        std::cout << reachables[i].count() << " ";
    }

    std::cout << "\n";
}
