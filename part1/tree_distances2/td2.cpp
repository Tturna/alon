/*
You are given a tree consisting of n nodes.
Your task is to determine for each node the sum of the distances from the node to all
other nodes.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered
1,2,...,n. Then there are n-1 lines describing the edges. Each line contains two integers
a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,...,n, the sum of the distances.

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
6 9 5 8 8
*/

#include <iostream>
#include <vector>

struct node {
    long long subTreeSize = 0;
    long long distancesSum = 0;
};

void calculateSubTreeData(int currentNode, int previousNode, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<node>& nodes) {
    nodes[currentNode].subTreeSize = 1;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        calculateSubTreeData(neighbor, currentNode, adjacencyTable, nodes);
        nodes[currentNode].subTreeSize += nodes[neighbor].subTreeSize;
        nodes[currentNode].distancesSum += nodes[neighbor].subTreeSize + nodes[neighbor].distancesSum;
    }
}

void updateDistanceSums(int currentNode, int previousNode, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<node>& nodes) {

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        nodes[neighbor].distancesSum = nodes[currentNode].distancesSum -
            nodes[neighbor].subTreeSize + (nodes.size() - nodes[neighbor].subTreeSize);
        updateDistanceSums(neighbor, currentNode, adjacencyTable, nodes);
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
    calculateSubTreeData(0, -1, adjacencyTable, nodes);
    updateDistanceSums(0, -1, adjacencyTable, nodes);

    for (int i = 0; i < nodeCount; i++) {
        std::cout << nodes[i].distancesSum << " ";
    }

    std::cout << "\n";
}
