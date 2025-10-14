#include <algorithm>
#include <iostream>
int main() {
    int a;
    int b;
    std::cin >> a;
    std::cin >> b;

    long long dp[a + 1][b + 1];

    // iterate all rectangles within given rectangle
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            // if sub-rect is square, skip because default value 0 is the answer
            if (i == j) continue;
            long long best = 1e9;

            // consider all possible vertical splits
            for (int k = 1; k < i; k++) {
                best = std::min(best, dp[k][j] + dp[i - k][j] + 1);
            }

            // consider all possible horizontal splits
            for (int k = 1; k < j; k++) {
                best = std::min(best, dp[i][k] + dp[i][j - k] + 1);
            }

            dp[i][j] = best;
        }
    }

    std::cout << dp[a][b] << "\n";
}
