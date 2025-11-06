/*
A company has n employees, who form a tree hierarchy where each employee has a boss,
except for the general director. Your task is to process q queries of the form:
who is the lowest common boss of employees a and b in the hierarchy?

Input

The first input line has two integers n and q: the number of employees and queries.
The employees are numbered 1,2,...,n, and employee 1 is the general director.
The next line has n-1 integers e_2,e_3,...,e_n: for each employee 2,3,...,n their boss.
Finally, there are q lines describing the queries. Each line has two integers a and b:
who is the lowest common boss of employees a and b?

Output

Print the answer for each query.

Constraints

1 <= n,q <= 2 * 10^5
1 <= e_i <= i-1
1 <= a,b <= n

Example
Input:
5 3
1 1 3 3
4 5
2 5
1 4

Output:
3
1
1
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void computeDepths(int currentNode, int previousNode, std::vector<std::vector<int>>& adjacencyTable,
    std::vector<int>& depths, int depth)
{
    depths[currentNode] = depth;

    for (auto neighbor : adjacencyTable[currentNode]) {
        if (neighbor == previousNode) continue;
        computeDepths(neighbor, currentNode, adjacencyTable, depths, depth + 1);
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
    int employeeCount;
    int queryCount;

    std::cin >> employeeCount >> queryCount;
    int maxExponent = 1;
    while (1 << maxExponent <= employeeCount) maxExponent++;
    std::vector<std::vector<int>> jumpTable(employeeCount, std::vector<int>(maxExponent, -1));
    std::vector<std::vector<int>> adjacencyTable(employeeCount);

    for (int i = 1; i < employeeCount; i++) {
        int boss;
        std::cin >> boss;
        jumpTable[i][0] = boss - 1;
        adjacencyTable[i].push_back(boss - 1);
        adjacencyTable[boss - 1].push_back(i);
    }

    for (int k = 1; k < maxExponent; k++) {
        for (int i = 1; i < employeeCount; i++) {
            int prev = jumpTable[i][k - 1];

            if (prev != -1) {
                jumpTable[i][k] = jumpTable[prev][k - 1];
            }
        }
    }

    std::vector<int> depths(employeeCount);
    computeDepths(0, -1, adjacencyTable, depths, 0);

    std::string result;

    for (int i = 0; i < queryCount; i++) {
        int a;
        int b;
        std::cin >> a >> b;

        int lca = lowestCommonAncestor(a - 1, b - 1, depths, maxExponent, jumpTable);
        result += std::to_string(lca + 1) + "\n";
    }

    std::cout << result;
}
