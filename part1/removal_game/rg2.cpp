/*
There is a list of n numbers and two players who move alternately. On each move, a player
removes either the first or last number from the list, and their score increases by that number.
Both players try to maximize their scores.

What is the maximum possible score for the first player when both players play optimally?

Input

The first input line contains an integer n: the size of the list.
The next line has n integers x_1,x_2,...,x_n: the contents of the list.

Output

Print the maximum possible score for the first player.

Constraints

1 <= n <= 5000
-10^9 <= x_i <= 10^9

Example
Input:
4
4 5 1 3

Output:
8
*/

#include <algorithm>
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    long long x[n];

    for (long long i = 0; i < n; i++) {
        std::cin >> x[i];
    }

    /*
    x[1, 2, 3]
    opt = max(
        1 + sum([2, 3]) - opt from [2, 3]

        3 + sum([1, 2]) - opt from [1, 2]
    )
    */

    long long dp[n][n];
    long long sums[n][n];

    if (n == 1) {
        dp[0][0] = x[0];
    }

    for (int l = n - 2; l >= 0; l--) {
        for (int r = l + 1; r < n; r++) {
            if (l + 1 == r) {
                dp[l][r] = std::max(x[l], x[r]);
                sums[l][r] = x[l] + x[r];
                continue;
            }

            long long leftChoice = x[l] + sums[l + 1][r] - dp[l + 1][r];
            long long rightChoice = x[r] + sums[l][r - 1] - dp[l][r - 1];
            dp[l][r] = std::max(leftChoice, rightChoice);
            sums[l][r] = x[l] + sums[l + 1][r];
        }
    }

    std::cout << dp[0][n - 1] << "\n";
}
