/*
You are playing a game consisting of n planets. Each planet has a teleporter to
another planet (or the planet itself). Your task is to process q queries of the form:
when you begin on planet x and travel through k teleporters, which planet will you reach?

Input

The first input line has two integers n and q: the number of planets and queries.
The planets are numbered 1,2,...,n. The second line has n integers t_1,t_2,...,t_n:
for each planet, the destination of the teleporter. It is possible that t_i=i.
Finally, there are q lines describing the queries. Each line has two integers x and k:
you start on planet x and travel through k teleporters.

Output

Print the answer to each query.

Constraints

1 <= n, q <= 2 * 10^5
1 <= t_i <= n
1 <= x <= n
0 <= k <= 10^9

Example
Input:
4 3
2 1 1 4
1 2
3 4
4 1

Output:
1
2
4
*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    int planetCount;
    int queryCount;

    std::cin >> planetCount;
    std::cin >> queryCount;

    int maxExponent = 30;
    // std::vector<std::vector<int>> jumpTable(planetCount, std::vector<int>(maxExponent + 1));
    std::vector<int> jumpTable(planetCount * (maxExponent + 1));
    std::vector<std::pair<int, int>> queries(queryCount);

    auto getDestReference = [&](int i, int k) -> int& {
        return jumpTable[k * planetCount + i];
    };

    for (int i = 0; i < planetCount; i++) {
        int teleportDestinationPlanet;
        std::cin >> teleportDestinationPlanet;
        // jumpTable[i][0] = teleportDestinationPlanet - 1;
        getDestReference(i, 0) = teleportDestinationPlanet - 1;
    }

    for (int i = 0; i < queryCount; i++) {
        int startingPlanet;
        int teleportCount;
        std::cin >> startingPlanet >> teleportCount;

        queries[i] = {startingPlanet - 1, teleportCount};
    }

    for (int k = 1; k <= maxExponent; k++) {
        for (int i = 0; i < planetCount; i++) {
            // jumpTable[i][k] = jumpTable[jumpTable[i][k - 1]][k - 1];
            getDestReference(i, k) = getDestReference(getDestReference(i, k - 1), k - 1);
        }
    }

    std::string result;
    result.reserve(queryCount * 8);

    for (int i = 0; i < queryCount; i++) {
        auto startingPlanet = queries[i].first;
        auto teleportCount = queries[i].second;

        // while (teleportCount > 0) {
        //     int stepExponent = static_cast<int>(std::floor(std::log2(teleportCount)));
        //     startingPlanet = jumpTable[startingPlanet][stepExponent];
        //     teleportCount -= std::pow(2, stepExponent);
        // }
        
        for (int bit = 0; bit <= maxExponent; bit++) {
            if (teleportCount & (1 << bit)) {
                // startingPlanet = jumpTable[startingPlanet][bit];
                startingPlanet = getDestReference(startingPlanet, bit);
            }
        }

        result += std::to_string(startingPlanet + 1) + "\n";
    }

    std::cout << result;
}
