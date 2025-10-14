/*
Your task is to build a tower whose width is 2 and height is n.
You have an unlimited supply of blocks whose width and height are integers.

Given n, how many different towers can you build? Mirrored and rotated towers are counted
separately if they look different.

Input

The first input line contains an integer t: the number of tests.
After this, there are t lines, and each line contains an integer n: the height of the tower.

Output

For each test, print the number of towers modulo 10^9+7.

Constraints

1 <= t <= 100
1 <= n <= 10^6

Example
Input:
3
2
6
1337

Output:
8
2864
640403945
*/

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int t;
    std::cin >> t;

    std::vector<unsigned long int> testHeights;
    unsigned long int maxHeight = 0;

    for (int i = 0; i < t; i++) {
        unsigned long int h;
        std::cin >> h;
        testHeights.push_back(h);
        maxHeight = std::max(maxHeight, h);
    }

    const unsigned long int MOD = 1000000007;
    std::vector<std::vector<unsigned long int>> dp(maxHeight + 1, std::vector<unsigned long int>(4, 0));
    std::vector<std::vector<int>> transitions(4, std::vector<int>(4, 1));
    transitions[0][0] = 2;
    transitions[0][3] = 2;

    dp[0][0] = 1;

    for (unsigned long int layer = 0; layer < maxHeight; layer++) {
        for (int mask = 0; mask < 4; mask++) {
            for (int nextMask = 0; nextMask < 4; nextMask++) {
                unsigned long int totalWaysToNextLayer = dp[layer + 1][nextMask];
                unsigned long int waysFromThisToNext = dp[layer][mask] * transitions[mask][nextMask];
                dp[layer + 1][nextMask] = (totalWaysToNextLayer + waysFromThisToNext) % MOD;
            }
        }
    }

    for (int i = 0; i < t; i++) {
        std::cout << dp[testHeights[i]][0] << "\n";
    }
}
