/*
Given an array of n integers, your task is to calculate the number of increasing
subsequences it contains. If two subsequences have the same values but in different
positions in the array, they are counted separately.

Input

The first input line has an integer n: the size of the array.
The second line has n integers x_1,x_2,...,x_n: the contents of the array.

Output

Print one integer: the number of increasing subsequences modulo 10^9+7.

Constraints

1 <= n <= 2 * 10^5
1 <= x_i <= 10^9

Example
Input:
3
2 1 3

Output:
5

Explanation: The increasing subsequences are [2], [1], [3], [2,3] and [1,3].
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

const int MOD = 1000000007;

void add(std::vector<long long>& tree, int treeSize, int k, int x) {
    k += treeSize;
    tree[k] += x;
    tree[k] %= MOD;

    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2 * k] + tree[2 * k + 1];
        tree[k] %= MOD;
    }
}

// laske välin a...b alkioiden summa
int getSum(std::vector<long long>& tree, int treeSize, int a, int b) {
    a += treeSize; b += treeSize;
    int s = 0;

    while (a <= b) {
        if (a % 2 == 1) s += tree[a++];
        s %= MOD;
        if (b % 2 == 0) s += tree[b--];
        s %= MOD;
        a /= 2; b /= 2;
    }
    return s;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vals(n);

    for (int i = 0; i < n; i++) {
        std::cin >> vals[i];
    }

    // increasing subsequences ending at i = sum of increasing subsequences of
    // elements before i whose values are less than the value at i. Add 1 to include value
    // at i alone.
    // dp[i] = 1 + sum(dp[0] ... dp[j]), where j < i and ignoring elements whose value is
    // not less than value at i.
    //
    // Total increasing subsequences is the sum of all increasing subsequences ending at
    // some specific index.
    // answer = sum(dp[0] ... dp[n - 1])

    // dp[i] = how many increasing subsequences end at th i'th element, including
    // the element itself.

    std::vector<int> sortedVals = vals;
    std::sort(sortedVals.begin(), sortedVals.end());
    std::unordered_map<int, int> ranks;
    int prev = -1;
    int uniqueRank = 0;

    for (int i = 0; i < n; i++) {
        int val = sortedVals[i];

        if (val == prev) {
            continue;
        }

        ranks[val] = uniqueRank++;
        prev = val;
    }

    int treeSize = 1;
    while (treeSize < uniqueRank) treeSize *= 2;

    std::vector<long long> dpTree(treeSize * 2, 0);

    // std::cout << "ranks:\n";
    // for (auto [val, rank] : ranks) {
    //     std::cout << val << ": " << rank << "\n";
    // }

    for (int i = 0; i < n; i++) {
        int rank = ranks[vals[i]];
        add(dpTree, treeSize, rank, 1 + getSum(dpTree, treeSize, 0, rank - 1));
    }

    // for (int i = 1; i < treeSize * 2; i++) {
    //     std::cout << dpTree[i] << " ";
    //
    //     if (i == treeSize - 1) {
    //         std::cout << "| ";
    //     }
    // }
    //
    // std::cout << "\n";

    std::cout << dpTree[1] << "\n";
}
