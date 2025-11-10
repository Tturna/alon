/*
Given a tree of n nodes, your task is to find a centroid, i.e., a node such that when it
is appointed the root of the tree, each subtree has at most floor(n/2) nodes.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b:
there is an edge between nodes a and b.

Output

Print one integer: a centroid node. If there are several possibilities, you can choose any of them.

Constraints

1 <= n <= 2 * 10^5
1 <= a,b <= n

Example
Input:
5
1 2
2 3
3 4
3 5

Output:
3
*/

#include <iostream>
#include <vector>

void calculateSubtreeSizes(int currentNode, int parent, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<int>& subtreeSizes)
{
    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == parent) continue;
        calculateSubtreeSizes(neighbor, currentNode, adjacencyTable, subtreeSizes);
        subtreeSizes[currentNode] += subtreeSizes[neighbor];
    }
}

int findCentroid(int currentNode, int parent, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<int>& subtreeSizes, int nodeCount) {
    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == parent) continue;
        if (subtreeSizes[neighbor] > nodeCount / 2) {
            return findCentroid(neighbor, currentNode, adjacencyTable, subtreeSizes, nodeCount);
        }
    }

    return currentNode;
}

int main() {
    int nodeCount;

    std::cin >> nodeCount;

    std::vector<std::vector<int>> adjacencyTable(nodeCount);

    for (int i = 0; i < nodeCount - 1; i++) {
        int a, b;
        std::cin >> a >> b;

        adjacencyTable[a - 1].push_back(b - 1);
        adjacencyTable[b - 1].push_back(a - 1);
    }

    std::vector<int> subtreeSizes(nodeCount, 1);
    calculateSubtreeSizes(0, -1, adjacencyTable, subtreeSizes);
    int centroid = findCentroid(0, -1, adjacencyTable, subtreeSizes, nodeCount);
    std::cout << centroid + 1 << "\n";
}
