/*
There are n cities and m roads between them. There is a route between any two cities.
A road is called necessary if there is no route between some two cities after
removing that road. Your task is to find all necessary roads.

Input

The first input line has two integers n and m: the number of cities and roads.
The cities are numbered 1,2,...,n. After this, there are m lines that describe the roads.
Each line has two integers a and b: there is a road between cities a and b. There is at
most one road between two cities, and every road connects two distinct cities.

Output

First print an integer k: the number of necessary roads. After that, print k lines that
describe the roads. You may print the roads in any order.

Constraints

2 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n

Example
Input:
5 5
1 2
1 4
2 4
3 5
4 5

Output:
2
3 5
4 5
*/

#include <algorithm>
#include <limits>
#include <utility>
#include <vector>
#include <iostream>

struct node {
    int discoveryDepth;
    int minReachableDepth;

    node() {
        this->discoveryDepth = 0;
        this->minReachableDepth = std::numeric_limits<int>::max();
    }
};

void makeTreeDfs(int currentNode, int previousNode, std::vector<bool>& visited, std::vector<std::vector<int>>& adjacencyTable,
    int& depth, std::vector<node>& nodes, std::vector<std::pair<int, int>>& treeEdges) {
    if (visited[currentNode]) {
        return;
    }

    visited[currentNode] = true;
    nodes[currentNode].discoveryDepth = depth;
    nodes[currentNode].minReachableDepth = depth;
    depth++;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        bool isNeighborVisited = visited[neighbor];

        if (!isNeighborVisited) {
            treeEdges.push_back({currentNode, neighbor});
        }

        makeTreeDfs(neighbor, currentNode, visited, adjacencyTable, depth, nodes, treeEdges);

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

int main() {
    int cityCount;
    int roadCount;

    std::cin >> cityCount;
    std::cin >> roadCount;

    std::vector<std::vector<int>> adjacencyTable(cityCount);

    for (int i = 0; i < roadCount; i++) {
        int from;
        int to;
        std::cin >> from;
        std::cin >> to;
        adjacencyTable[from - 1].push_back(to - 1);
        adjacencyTable[to - 1].push_back(from - 1);
    }

    std::vector<bool> visited(cityCount, false);
    std::vector<node> nodes(cityCount);
    std::vector<std::pair<int, int>> treeEdges;

    // All cities are connected by default so assume 1 DFS pass suffices
    int depth = 0;
    makeTreeDfs(0, 0, visited, adjacencyTable, depth, nodes, treeEdges);

    // for (int i = 0; i < cityCount; i++) {
    //     auto node = nodes[i];
    //     std::cout << "node " << i + 1 << ": " << node.discoveryDepth << ", " << node.minReachableDepth << "\n";
    // }

    std::vector<std::pair<int, int>> bridges;
    
    for (auto edge : treeEdges) {
        int from = edge.first;
        int to = edge.second;

        if (nodes[to].minReachableDepth > nodes[from].discoveryDepth) {
            bridges.push_back(edge);
        }
    }

    std::cout << bridges.size() << "\n";

    for (auto bridge : bridges) {
        std::cout << bridge.first + 1 << " " << bridge.second + 1 << "\n";
    }
}
