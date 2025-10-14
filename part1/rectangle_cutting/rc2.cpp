
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    const int INF = 1e9;
    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j) continue;
            int best = INF;

            // horizontal cuts
            for (int k = 1; k < i; k++)
                best = min(best, dp[k][j] + dp[i - k][j] + 1);

            // vertical cuts
            for (int k = 1; k < j; k++)
                best = min(best, dp[i][k] + dp[i][j - k] + 1);

            dp[i][j] = best;
        }
    }

    cout << dp[a][b] << "\n";
}
