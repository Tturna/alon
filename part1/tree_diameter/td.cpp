/*
You are given a tree consisting of n nodes.
The diameter of a tree is the maximum distance between two nodes. Your task is to
determine the diameter of the tree.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered
1,2,...,n. Then there are n-1 lines describing the edges. Each line contains two integers
a and b: there is an edge between nodes a and b.

Output

Print one integer: the diameter of the tree.

Constraints

1 <= n <= 2 * 10^5
1 <= a,b <= n

Example
Input:
5
1 2
1 3
3 4
3 5

Output:
3

Explanation: The diameter corresponds to the path 2 -> 1 -> 3 -> 5.
*/

#include <iostream>
#include <vector>

struct node {
    int maxSubTreeLength = 0;
    int secondMaxSubTreeLength = 0;
};

void getDepthsDfs(int currentNode, int previousNode, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<node>& nodes, node& maxNode) {

    nodes[currentNode].maxSubTreeLength = 0;
    nodes[currentNode].secondMaxSubTreeLength = 0;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;
        getDepthsDfs(neighbor, currentNode, adjacencyTable, nodes, maxNode);

        int nLength = nodes[neighbor].maxSubTreeLength + 1;

        if (nLength > nodes[currentNode].maxSubTreeLength) {
            nodes[currentNode].secondMaxSubTreeLength = nodes[currentNode].maxSubTreeLength;
            nodes[currentNode].maxSubTreeLength = nLength;
        }
        else if (nLength > nodes[currentNode].secondMaxSubTreeLength) {
            nodes[currentNode].secondMaxSubTreeLength = nLength;
        }
    }

    int maxPathLength = nodes[currentNode].maxSubTreeLength + nodes[currentNode].secondMaxSubTreeLength;

    if (maxPathLength > maxNode.maxSubTreeLength + maxNode.secondMaxSubTreeLength) {
        maxNode = nodes[currentNode];
    }
}

int main() {
    int nodeCount;
    std::cin >> nodeCount;

    std::vector<std::vector<int>> adjacencyTable(nodeCount);

    for (int i = 0; i < nodeCount - 1; i++) {
        int from;
        int to;
        std::cin >> from >> to;
        adjacencyTable[from - 1].push_back(to - 1);
        adjacencyTable[to - 1].push_back(from - 1);
    }

    std::vector<node> nodes(nodeCount);
    node maxNode = nodes[0];
    getDepthsDfs(0, -1, adjacencyTable, nodes, maxNode);

    std::cout << maxNode.maxSubTreeLength + maxNode.secondMaxSubTreeLength << "\n";
}
