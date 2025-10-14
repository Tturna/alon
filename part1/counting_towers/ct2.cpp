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
    
    // dp[h][mask] = number of ways to build to height h with given top profile
    // mask: 0=00 (both empty), 1=01 (right occupied), 2=10 (left occupied), 3=11 (both occupied)
    std::vector<std::vector<unsigned long int>> dp(maxHeight + 1, std::vector<unsigned long int>(4, 0));
    
    // Transition table: transitions[currentMask][nextMask] = number of ways
    std::vector<std::vector<unsigned long int>> transitions(4, std::vector<unsigned long int>(4, 0));
    
    // From 00 (both empty): must fill both
    // - Two 1-wide blocks of height 1 each -> 00
    // - One 2-wide block of height 1 -> 00
    // - Two 1-wide blocks continuing -> 11
    // - One 2-wide block continuing -> 11
    // - Left continues, right ends -> 10
    // - Right continues, left ends -> 01
    transitions[0][0] = 2;  // Both end at next layer
    transitions[0][1] = 1;  // Right continues, left ends
    transitions[0][2] = 1;  // Left continues, right ends
    transitions[0][3] = 2;  // Both continue
    
    // From 01 (right occupied, left empty): must fill left
    // - 1-wide block height 1 -> 00
    // - 1-wide block continues -> 10
    transitions[1][0] = 1;  // Left ends
    transitions[1][2] = 1;  // Left continues
    
    // From 10 (left occupied, right empty): must fill right
    // - 1-wide block height 1 -> 00
    // - 1-wide block continues -> 01
    transitions[2][0] = 1;  // Right ends
    transitions[2][1] = 1;  // Right continues
    
    // From 11 (both occupied): nothing to fill
    // - Both end -> 00
    transitions[3][0] = 1;
    
    dp[0][0] = 1;

    for (unsigned long int layer = 0; layer < maxHeight; layer++) {
        for (int mask = 0; mask < 4; mask++) {
            if (dp[layer][mask] == 0) continue;
            for (int nextMask = 0; nextMask < 4; nextMask++) {
                if (transitions[mask][nextMask] > 0) {
                    unsigned long int waysFromThisToNext = (dp[layer][mask] * transitions[mask][nextMask]) % MOD;
                    dp[layer + 1][nextMask] = (dp[layer + 1][nextMask] + waysFromThisToNext) % MOD;
                }
            }
        }
    }

    for (int i = 0; i < t; i++) {
        std::cout << dp[testHeights[i]][0] << "\n";
    }

    return 0;
}
