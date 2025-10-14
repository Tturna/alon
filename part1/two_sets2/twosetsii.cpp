/*
Your task is to count the number of ways numbers 1,2,...,n can be divided into two sets
of equal sum.
For example, if n=7, there are four solutions:

{1,3,4,6} and {2,5,7}
{1,2,5,6} and {3,4,7}
{1,2,4,7} and {3,5,6}
{1,6,7} and {2,3,4,5}

Input

The only input line contains an integer n.

Output

Print the answer modulo 10^9+7.

Constraints

1 <= n <= 500

Example
Input:
7

Output:
4
*/

#include <iostream>
int main() {
    int n;
    std::cin >> n;

    int maxSum = (n * (n + 1)) / 2;

    if (maxSum % 2 != 0) {
        std::cout << 0 << "\n";
        return 0;
    }

    int target = maxSum / 2;
    long long dp[n + 1][target + 1];

    dp[0][0] = 1;

    for (int i = 1; i <= target; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            auto subarrsWithoutNum = dp[i - 1][j];
            auto subarssWithNum = j >= i ? dp[i - 1][j - i] : 0;
            dp[i][j] = (subarrsWithoutNum + subarssWithNum) % 1000000007;
        }
    }

    long long modInverseOfTwo = (1000000007 + 1LL) / 2;

    std::cout << (dp[n][target] * modInverseOfTwo) % 1000000007 << "\n";
}
