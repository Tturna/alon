/*
Byteland has n cities, and m roads between them. The goal is to construct new roads so that
there is a route between any two cities. Your task is to find out the minimum number of roads
required, and also determine which roads should be built.

Input

The first input line has two integers n and m: the number of cities and roads. The cities are
numbered 1,2,...,n. After that, there are m lines describing the roads. Each line has two
integers a and b: there is a road between those cities. A road always connects two different
cities, and there is at most one road between any two cities.

Output

First print an integer k: the number of required roads.
Then, print k lines that describe the new roads. You can print any valid solution.

Constraints

1 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n

Example
Input:
4 2
1 2
3 4

Output:
1
2 3
*/

#include <iostream>
#include <utility>
#include <vector>

void dfs(int node, std::vector<bool>& visited, std::vector<std::vector<int>>& adjacencies) {
    if (visited[node]) return;

    visited[node] = true;
    auto neighbors = adjacencies[node];

    for (unsigned int i = 0; i < neighbors.size(); i++) {
        dfs(neighbors[i], visited, adjacencies);
    }
}

int main() {
    int cityCount;
    int roadCount;
    std::cin >> cityCount;
    std::cin >> roadCount;

    std::vector<std::vector<int>> adjacencies(cityCount);

    for (int i = 0; i < roadCount; i++) {
        int a;
        int b;
        std::cin >> a;
        std::cin >> b;
        adjacencies[a - 1].push_back(b - 1);
        adjacencies[b - 1].push_back(a - 1);
    }

    // for (int i = 0; i < cityCount; i++) {
    //     std::cout << i + 1 << ": ";;
    //     auto adjacents = adjacencies[i];
    //
    //     for (unsigned int j = 0; j < adjacents.size(); j++) {
    //         std::cout << adjacencies[i][j] + 1 << " ";
    //     }
    //
    //     std::cout << "\n";
    // }

    std::vector<bool> visited(cityCount);
    std::vector<std::pair<int, int>> newRoads;
    int components = 0;
    int lastConnectionNode = 0;

    for (int i = 0; i < cityCount; i++) {
        if (visited[i]) continue;

        dfs(i, visited, adjacencies);
        components++;

        if (components <= 1) continue;

        newRoads.push_back(std::pair<int, int>(lastConnectionNode, i));
        lastConnectionNode = i;
    }

    std::cout << components - 1 << "\n";

    for (auto nr : newRoads) {
        std::cout << nr.first + 1 << " " << nr.second + 1 << "\n";
    }
}
