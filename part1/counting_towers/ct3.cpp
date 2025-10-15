#include <iostream>
#include <vector>

int main() {
    const long long MOD = 1e9 + 7;
    int t;
    std::cin >> t;
    std::vector<int> testHeights;
    int maxHeight = 0;

    for (int i = 0; i < t; i++) {
        int h;
        std::cin >> h;
        testHeights.push_back(h);
        maxHeight = std::max(maxHeight, h);
    }

    // dp0 values represent the number of ways to make a tower of the given height, where
    // the top is aligned (both columns end at the same height).
    // dp1 is the same for towers that have a staggered top.
    std::vector<long long> dp0(maxHeight + 1);
    std::vector<long long> dp1(maxHeight + 1);
    dp0[1] = dp1[1] = 1;

    // if the previous tower is aligned, you can keep it aligned in 2 ways:
    // 1. add a 1x1 block to each column
    // 2. add a 2x1 horizontal block
    // To combine possibilities you multiply them. So if there are 2 ways to keep
    // the previous top aligned when you add a row, the total number of ways to build that tower
    // is the number of ways to build the previous one times 2. So it's 2 * dp0[layer - 1].
    // If the previous layer has a staggered top, you can only fix it one way.
    // So the total number of ways to build an aligned tower at layer n is
    // 2 * dp0[layer - 1] + dp1[layer - 1].
    for (int i = 2; i <= maxHeight; i++) {
        dp0[i] = (2 * dp0[i - 1] + dp1[i - 1]) % MOD;
        // Note entirely sure why there are 4 and not 3 ways to keep a staggered tower staggered...
        dp1[i] = (dp0[i - 1] + 4 * dp1[i - 1]) % MOD;
    }

    for (int n : testHeights) {
        // if you can make an aligned tower of height n in dp0[n] ways and
        // a staggered one in dp1[n] ways, the total number of ways to build a tower
        // of height n is just those added together.
        std::cout << (dp0[n] + dp1[n]) % MOD << "\n";
    }
}
