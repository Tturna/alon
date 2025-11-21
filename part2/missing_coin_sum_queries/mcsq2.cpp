/*
You have n coins with positive integer values. The coins are numbered 1,2,...,n.
Your task is to process q queries of the form: "if you can use coins a ... b, what is
the smallest sum you cannot produce?"

Input

The first input line has two integers n and q: the number of coins and queries.
The second line has n integers x_1,x_2,...,x_n: the value of each coin.
Finally, there are q lines that describe the queries. Each line has two values a and b:
you can use coins a ... b.

Output

Print the answer for each query.

Constraints

1 <= n, q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n

Example
Input:
5 3
2 9 1 2 7
2 4
4 4
1 5

Output:
4
1
6

Explanation: First you can use coins [9,1,2], then coins [2] and finally coins [2,9,1,2,7].
*/

#include <algorithm>
#include <iostream>
#include <vector>

long long getMinSum(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    long long ref = 1;
    auto it = start;

    if (*it != 1) return ref;

    while (it <= end) {
        if (ref >= *it) {
            ref += *it;
            it++;
            continue;
        }

        break;
    }

    return ref;
}

void buildMergeSortTree(std::vector<std::vector<int>>& tree, int treeSize, std::vector<int>& values) {
    for (int i = 0; i < (int)values.size(); i++) {
        tree[treeSize + i] = {values[i]};
    }

    for (int i = treeSize - 1; i > 0; i--) {
        std::vector<int>& left = tree[i * 2];
        std::vector<int>& right = tree[i * 2 + 1];
        tree[i].resize(left.size() + right.size());
        std::merge(left.begin(), left.end(), right.begin(), right.end(), tree[i].begin());
    }
}

std::vector<int> queryMergeSortTree(std::vector<std::vector<int>>& tree, int treeSize, int left, int right) {
    left += treeSize;
    right += treeSize;
    std::vector<int> result;

    while (left <= right) {
        if (left % 2 == 1) {
            result.insert(result.end(), tree[left].begin(), tree[left].end());
            left++;
        }

        if (right % 2 == 0) {
            result.insert(result.end(), tree[right].begin(), tree[right].end());
            right--;
        }

        left /= 2;
        right /= 2;
    }

    sort(result.begin(), result.end());
    return result;
}

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> coins(n);

    for (int i = 0; i < n; i++) {
        std::cin >> coins[i];
    }

    int treeSize = 1;
    while (treeSize < n) treeSize *= 2;

    std::vector<std::vector<int>> mergeSortTree(2 * treeSize, std::vector<int>());
    buildMergeSortTree(mergeSortTree, treeSize, coins);

    // std::cout << "tree:\n";
    // for (int i = 0; i < 2 * treeSize; i++) {
    //     for (auto v : sTree[i]) {
    //         std::cout << v << " ";
    //     }
    //     std::cout << "\n";
    // }

    std::string result;

    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a >> b;
        auto sortedRange = queryMergeSortTree(mergeSortTree, treeSize, a - 1, b - 1);
        auto start = sortedRange.begin();
        auto end = sortedRange.end() - 1;

        result += std::to_string(getMinSum(start, end)) + "\n";
    }

    std::cout << result;
}
