/*
There are n cities and m roads between them. There is a route between any two cities.
A city is called necessary if there is no route between some other two cities after
removing that city (and adjacent roads). Your task is to find all necessary cities.

Input

The first input line has two integers n and m: the number of cities and roads. The
cities are numbered 1,2,...,n. After this, there are m lines that describe the roads.
Each line has two integers a and b: there is a road between cities a and b. There is at
most one road between two cities, and every road connects two distinct cities.

Output

First print an integer k: the number of necessary cities. After that, print a list of k
cities. You may print the cities in any order.

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
4 5
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

struct node {
    int discoveryOrder;
    int minReachableOrder;

    node() {
        this->discoveryOrder = 0;
        this->minReachableOrder = std::numeric_limits<int>::max();
    }
};

void makeTreeDfs(int currentNode, int previousNode, std::vector<bool>& visited,
    std::vector<std::vector<int>>& adjacencyTable, int& order, std::vector<node>& nodes,
    std::vector<std::pair<int, int>>& treeEdges) {
    if (visited[currentNode]) return;

    visited[currentNode] = true;
    nodes[currentNode].discoveryOrder = order;
    nodes[currentNode].minReachableOrder = order;
    order++;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        bool isNeighborVisited = visited[neighbor];

        if (!isNeighborVisited) {
            treeEdges.push_back({currentNode, neighbor});
        }

        makeTreeDfs(neighbor, currentNode, visited, adjacencyTable, order, nodes, treeEdges);

        if (isNeighborVisited) {
            nodes[currentNode].minReachableOrder = std::min(nodes[currentNode].minReachableOrder,
                nodes[neighbor].discoveryOrder);
        }
        else {
            nodes[currentNode].minReachableOrder = std::min(nodes[currentNode].minReachableOrder,
                nodes[neighbor].minReachableOrder);
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
        std::cin >> from >> to;
        adjacencyTable[from - 1].push_back(to - 1);
        adjacencyTable[to - 1].push_back(from - 1);
    }

    std::vector<bool> visited(cityCount);
    std::vector<node> nodes(cityCount);
    std::vector<std::pair<int, int>> treeEdges;
    int order = 0;
    makeTreeDfs(0, 0, visited, adjacencyTable, order, nodes, treeEdges);

    std::vector<std::vector<int>> treeAdjacencies(cityCount);

    for (auto edge : treeEdges) {
        treeAdjacencies[edge.first].push_back(edge.second);
        treeAdjacencies[edge.second].push_back(edge.first);
    }

    std::vector<int> articulationPoints;

    for (int i = 0; i < cityCount; i++) {
        auto node = nodes[i];
        // std::cout << "node " << i + 1 << ": " << node.discoveryOrder << ", " << node.minReachableOrder << "\n";

        // node is articulation point if it's the first DFS node,
        // it has multiple children, and none of its children
        // have multiple paths to it (min reachable discovery order > 0)
        if (i == 0) {
            // node is DFS root node
            
            if (treeAdjacencies[i].size() <= 1) {
                // root doesn't have multiple children -> not articulation point
                continue;
            }

            bool allChildrenHaveAlts = true;
            for (auto child : treeAdjacencies[0]) {
                if (nodes[child].minReachableOrder > 0) {
                    allChildrenHaveAlts = false;
                    break;
                }
            }

            // root has multiple children, but all children have alternate paths
            // -> not articulation point
            if (allChildrenHaveAlts) {
                continue;
            }

            articulationPoints.push_back(0);
            continue;
        }

        // node is not DFS root

        // node has no children -> not articulation point
        if (adjacencyTable[i].size() == 0) continue;

        bool allChildrenHaveAlts = true;
        for (auto child : treeAdjacencies[i]) {
            if (nodes[child].minReachableOrder >= nodes[i].discoveryOrder) {
                allChildrenHaveAlts = false;
                break;
            }
        }

        // all of node's children can reach the node or an ancestor from another path
        // -> not articulation point
        if (allChildrenHaveAlts) {
            continue;
        }

        articulationPoints.push_back(i);
    }

    std::cout << articulationPoints.size() << "\n";

    for (auto ap : articulationPoints) {
        std::cout << ap + 1 << " ";
    }

    std::cout << "\n";
}
