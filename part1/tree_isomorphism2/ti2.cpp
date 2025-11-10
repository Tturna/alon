/*
Given two (not rooted) trees, your task is to find out if they are isomorphic, i.e.,
it is possible to draw them so that they look the same.

Input

The first input line has an integer t: the number of tests. Then, there are t tests
described as follows: The first line has an integer n: the number of nodes in both
trees. The nodes are numbered 1,2,...,n. Then, there are n-1 lines describing
the edges of the first tree, and finally n-1 lines describing the edges of the second tree.

Output

For each test, print "YES", if the trees are isomorphic, and "NO" otherwise.

Constraints

1 <= t <= 1000
2 <= n <= 10^5
the sum of all values of n is at most 10^5

Example
Input:
2
3
1 2
2 3
1 2
1 3
3
1 2
2 3
1 3
3 2

Output:
YES
YES
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::vector<int>, int> labelMap;
int nextLabel = 2;

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
    std::vector<int>& subtreeSizes, int nodeCount)
{
    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == parent) continue;
        if (subtreeSizes[neighbor] > nodeCount / 2) {
            return findCentroid(neighbor, currentNode, adjacencyTable, subtreeSizes, nodeCount);
        }
    }

    return currentNode;
}

int labelNode(int node, int parent, std::vector<std::vector<int>>& adjacencyTable) {
    std::vector<int> childLabels;

    for (auto neighbor : adjacencyTable[node]) {
        if (neighbor == parent) continue;
        childLabels.push_back(labelNode(neighbor, node, adjacencyTable));
    }

    if (childLabels.empty()) {
        return 1;
    }

    std::sort(childLabels.begin(), childLabels.end());

    // count() returns 1 or 0 based on if the given key exists (because we use map and not multimap).
    if (!labelMap.count(childLabels)) {
        labelMap[childLabels] = nextLabel;
        nextLabel++;
    }

    return labelMap[childLabels];
}

int main() {
    int testCount;

    std::cin >> testCount;
    std::string result;

    for (int i = 0; i < testCount; i++) {
        int nodeCount;
        std::cin >> nodeCount;

        labelMap.clear();
        nextLabel = 2;
        std::vector<std::vector<int>> adjacencyTable(nodeCount);

        for (int n = 0; n < nodeCount - 1; n++) {
            int from;
            int to;
            std::cin >> from >> to;
            adjacencyTable[from - 1].push_back(to - 1);
            adjacencyTable[to - 1].push_back(from - 1);
        }

        std::vector<int> subtreeSizes(nodeCount, 1);
        calculateSubtreeSizes(0, -1, adjacencyTable, subtreeSizes);
        int centroid = findCentroid(0, -1, adjacencyTable, subtreeSizes, nodeCount);
        int leftLabel = labelNode(centroid, -1, adjacencyTable);

        // find possible alt centroid. If there is a second centroid, it should
        // always be next to the first one.
        for (auto centroidNeighbor : adjacencyTable[centroid]) {
            int neighborSize = subtreeSizes[centroidNeighbor];
            int centroidSize = nodeCount - neighborSize;

            if (neighborSize > nodeCount / 2 || centroidSize > nodeCount / 2) continue;

            int altLabel = labelNode(centroidNeighbor, -1, adjacencyTable);
            leftLabel = std::min(leftLabel, altLabel);
            break;
        }

        // labelMap.clear();
        adjacencyTable.clear();
        adjacencyTable = std::vector<std::vector<int>>(nodeCount);
        subtreeSizes.clear();
        subtreeSizes = std::vector<int>(nodeCount, 1);
        // nextLabel = 2;

        for (int n = 0; n < nodeCount - 1; n++) {
            int from;
            int to;
            std::cin >> from >> to;
            adjacencyTable[from - 1].push_back(to - 1);
            adjacencyTable[to - 1].push_back(from - 1);
        }

        calculateSubtreeSizes(0, -1, adjacencyTable, subtreeSizes);
        centroid = findCentroid(0, -1, adjacencyTable, subtreeSizes, nodeCount);
        int rightLabel = labelNode(centroid, -1, adjacencyTable);

        for (auto centroidNeighbor : adjacencyTable[centroid]) {
            int neighborSize = subtreeSizes[centroidNeighbor];
            int centroidSize = nodeCount - neighborSize;

            if (neighborSize > nodeCount / 2 || centroidSize > nodeCount / 2) continue;

            int altLabel = labelNode(centroidNeighbor, -1, adjacencyTable);
            rightLabel = std::min(rightLabel, altLabel);
            break;
        }

        result += leftLabel == rightLabel ? "YES\n" : "NO\n";
    }

    std::cout << result;
}
