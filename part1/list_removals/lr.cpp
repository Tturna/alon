/*
You are given a list consisting of n integers. Your task is to remove elements from the list
at given positions, and report the removed elements.

Input

The first input line has an integer n: the initial size of the list. During the process,
the elements are numbered 1,2,...,k where k is the current size of the list.
The second line has n integers x_1,x_2,...,x_n: the contents of the list.
The last line has n integers p_1,p_2,...,p_n: the positions of the elements to be removed.

Output

Print the elements in the order they are removed.

Constraints

1 <= n <= 2 * 10^5
1 <= x_i <= 10^9
1 <= p_i <= n-i+1

Example
Input:
5
2 6 1 4 2
3 1 3 1 1

Output:
1 2 2 6 4

Explanation: The contents of the list are [2,6,1,4,2], [2,6,4,2], [6,4,2], [6,4], [4] and [].
*/

#include <iostream>
#include <vector>
int main() {
    long n;
    std::cin >> n;

    std::vector<long> list(n);
    std::vector<long> toBeRemoved(n);

    for (long i = 0; i < n; i++) {
        std::cin >> list[i];
    }

    for (long i = 0; i < n; i++) {
        std::cin >> toBeRemoved[i];
    }

    long treeSize = 1;

    while (treeSize < n) {
        treeSize *= 2;
    }

    std::vector<long> existenceSumTree(2 * treeSize, 0);

    // leaves
    for (long i = 0; i < n; i++) {
        existenceSumTree[treeSize + i] = 1;
    }

    // internal nodes
    for (long i = treeSize - 1; i > 0; i--) {
        existenceSumTree[i] = existenceSumTree[2 * i] + existenceSumTree[2 * i + 1];
    }

    // std::cout << "existence sum tree:\n";
    //
    // for (auto val : existenceSumTree) {
    //     std::cout << val << " ";
    // }

    for (long i = 0; i < n; i++) {
        long indexToRemove = toBeRemoved[i];
        long k = 1;

        while (k < treeSize) {
            if (existenceSumTree[2 * k] < indexToRemove) {
                indexToRemove -= existenceSumTree[2 * k];
                k = 2 * k + 1;
            }
            else {
                k *= 2;
            }
        }

        std::cout << list[k - treeSize] << " ";

        existenceSumTree[k] = 0;
        for (k /= 2; k >= 1; k /= 2) {
            existenceSumTree[k] = existenceSumTree[2 * k] + existenceSumTree[2 * k + 1];
        }
    }

    std::cout << "\n";
}
