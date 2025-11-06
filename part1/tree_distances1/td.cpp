/*
You are given a tree consisting of n nodes.
Your task is to determine for each node the maximum distance to another node.

Input

The first input line contains an integer n: the number of nodes. The nodes are
numbered 1,2,...,n. Then there are n-1 lines describing the edges. Each line contains
two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,...,n, the maximum distance to another node.

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
2 3 2 3 3
*/

#include <algorithm>
#include <iostream>
#include <vector>

void getChildPathLengths(int currentNode, int previousNode,
    std::vector<std::vector<int>>& adjacencyTable, std::vector<int>& downwardsLengths)
{
    downwardsLengths[currentNode] = 0;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        getChildPathLengths(neighbor, currentNode, adjacencyTable, downwardsLengths);
        downwardsLengths[currentNode] = std::max(downwardsLengths[currentNode],
            downwardsLengths[neighbor] + 1);
    }
}

void updateMaxPathLengths(int currentNode, int previousNode,
    std::vector<std::vector<int>>& adjacencyTable, std::vector<int>& lengths,
    std::vector<int>& maxUpwardsLengths)
{
    int maxChildPath = -1;
    int secondMaxChildPath = -1;

    // get longest and second longest path in children
    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        if (lengths[neighbor] > maxChildPath) {
            secondMaxChildPath = maxChildPath;
            maxChildPath = lengths[neighbor];
        }
        else if (lengths[neighbor] > secondMaxChildPath) {
            secondMaxChildPath = lengths[neighbor];
        }
    }

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;

        // when considering the longest path for a neighbor, compare against the longest
        // available path that does not start with the neighbor itself
        int otherPathLength = lengths[neighbor] == maxChildPath ? secondMaxChildPath : maxChildPath;

        // a node's max path is either its own sub-path or the sibling path + 2 steps to
        // reach the sibling via parent node
        maxUpwardsLengths[neighbor] = std::max(maxUpwardsLengths[currentNode] + 1, otherPathLength + 2);
        updateMaxPathLengths(neighbor, currentNode, adjacencyTable, lengths, maxUpwardsLengths);
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

    std::vector<int> downwardsLengths(nodeCount);
    getChildPathLengths(0, -1, adjacencyTable, downwardsLengths);

    // for (int i = 0; i < nodeCount; i++) {
    //     std::cout << "node " << i + 1 << " max child path len: " << downwardsLengths[i] << "\n";
    // }

    std::vector<int> maxUpwardsLengths(nodeCount);
    maxUpwardsLengths[0] = 0;
    updateMaxPathLengths(0, -1, adjacencyTable, downwardsLengths, maxUpwardsLengths);

    for (int i = 0; i < nodeCount; i++) {
        std::cout << std::max(maxUpwardsLengths[i], downwardsLengths[i]) << " ";
    }

    std::cout << "\n";
}
