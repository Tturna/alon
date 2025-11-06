/*
You are given a tree consisting of n nodes.
Your task is to process q queries of the form: what is the distance between nodes a and b?

Input

The first input line contains two integers n and q: the number of nodes and queries. The
nodes are numbered 1,2,...,n. Then there are n-1 lines describing the edges. Each line
contains two integers a and b: there is an edge between nodes a and b. Finally, there are
q lines describing the queries. Each line contains two integer a and b: what is the distance
between nodes a and b?

Output

Print q integers: the answer to each query.

Constraints

1 <= n, q <= 2 * 10^5
1 <= a,b <= n

Example
Input:
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4

Output:
1
3
2

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void computeDepths(int currentNode, int previousNode, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<int>& depths, int depth, std::vector<std::vector<int>>& jumpTable)
{
    depths[currentNode] = depth;
    jumpTable[currentNode][0] = previousNode;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;
        computeDepths(neighbor, currentNode, adjacencyTable, depths, depth + 1, jumpTable);
    }
}

int lowestCommonAncestor(int a, int b, std::vector<int>& depths, int maxExponent,
    std::vector<std::vector<int>>& jumpTable) {
    int aDepth = depths[a];
    int bDepth = depths[b];
    int lowerDepth = std::min(aDepth, bDepth);
    int lower;
    int higher;

    // lower depth = higher in the tree (closer to root)
    if (lowerDepth == aDepth) {
        higher = a;
        lower = b;
    }
    else {
        higher = b;
        lower = a;
    }

    if (depths[lower] > depths[higher]) {
        int diff = depths[lower] - depths[higher];

        for (int j = 0; j < maxExponent; j++) {
            if (diff & (1 << j)) {
                lower = jumpTable[lower][j];
            }
        }
    }

    if (lower == higher) return lower;

    for (int j = maxExponent - 1; j >= 0; j--) {
        if (jumpTable[lower][j] == jumpTable[higher][j]) continue;

        lower = jumpTable[lower][j];
        higher = jumpTable[higher][j];
    }

    return jumpTable[lower][0];
}

int main() {
    int nodeCount;
    int queryCount;

    std::cin >> nodeCount >> queryCount;
    int maxExponent = 1;
    while (1 << maxExponent <= nodeCount) maxExponent++;
    std::vector<std::vector<int>> jumpTable(nodeCount, std::vector<int>(maxExponent, -1));
    std::vector<std::vector<int>> adjacencyTable(nodeCount);

    for (int i = 0; i < nodeCount - 1; i++) {
        int from;
        int to;
        std::cin >> from >> to;
        adjacencyTable[from - 1].push_back(to - 1);
        adjacencyTable[to - 1].push_back(from - 1);
    }

    std::vector<int> depths(nodeCount);
    computeDepths(0, -1, adjacencyTable, depths, 0, jumpTable);

    for (int k = 1; k < maxExponent; k++) {
        for (int i = 1; i < nodeCount; i++) {
            int prev = jumpTable[i][k - 1];

            if (prev != -1) {
                jumpTable[i][k] = jumpTable[prev][k - 1];
            }
        }
    }

    std::string result;

    for (int i = 0; i < queryCount; i++) {
        int a;
        int b;
        std::cin >> a >> b;

        int lca = lowestCommonAncestor(a - 1, b - 1, depths, maxExponent, jumpTable);
        int distance = depths[a - 1] + depths[b - 1] - 2 * depths[lca];
        result += std::to_string(distance) + "\n";
    }

    std::cout << result;
}
