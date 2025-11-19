/*
There is a bit string consisting of n bits. Then, there are some changes that invert one
given bit. Your task is to report, after each change, the length of the longest substring
whose each bit is the same.

Input

The first input line has a bit string consisting of n bits. The bits are numbered 1,2,...,n.
The next line contains an integer m: the number of changes.
The last line contains m integers x_1,x_2,...,x_m describing the changes.

Output

After each change, print the length of the longest substring whose each bit is the same.

Constraints

1 <= n <= 2 * 10^5
1 <= m <= 2 * 10^5
1 <= x_i <= n

Example
Input:
001011
3
3 2 5

Output:
4 2 3

Explanation: The bit string first becomes 000011, then 010011, and finally 010001.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct node {
    int length;
    int prefixRun;
    int suffixRun;
    int maxRun;

    node(int length, int prefixRun, int suffixRun, int maxRun) {
        this->length = length;
        this->prefixRun = prefixRun;
        this->suffixRun = suffixRun;
        this->maxRun = maxRun;
    }
};

node merge(node& left, node& right) {
    int length = left.length + right.length;
    int prefixRun = left.prefixRun < left.length ? left.prefixRun : left.length + right.prefixRun;
    int suffixRun = right.suffixRun < right.length ? right.suffixRun : right.length + left.suffixRun;
    int maxRun = std::max(std::max(left.maxRun, right.maxRun), left.suffixRun + right.prefixRun);
    return node(length, prefixRun, suffixRun, maxRun);
}

void flipBit(std::vector<node>& oneTree, std::vector<node>& zeroTree, int treeSize, int k) {
    k += treeSize;
    node bitNode = oneTree[k];
    node invNode = bitNode;
    int val = bitNode.maxRun == 1 ? 0 : 1;
    bitNode.maxRun = val;
    bitNode.prefixRun = val;
    bitNode.suffixRun = val;
    oneTree[k] = bitNode;
    zeroTree[k] = invNode;

    for (k /= 2; k >= 1; k /= 2) {
        oneTree[k] = merge(oneTree[2 * k], oneTree[2 * k + 1]);
        zeroTree[k] = merge(zeroTree[2 * k], zeroTree[2 * k + 1]);
    }
}

int main() {
    std::string bitString;
    int m;
    std::cin >> bitString >> m;
    int n = bitString.size();
    std::vector<int> changes(m);

    for (int i = 0; i < m; i++) {
        std::cin >> changes[i];
        changes[i]--;
    }

    int treeSize = 1;
    while (treeSize < n) treeSize *= 2;

    std::vector<node> oneTree(treeSize * 2, node(1, 0, 0, 0));
    std::vector<node> zeroTree(treeSize * 2, node(1, 0, 0, 0));

    for (int i = 0; i < n; i++) {
        char c = bitString[i];
        // get 0 or 1 as integer. 48 maps to '0' in ASCII
        int val = c - '0';
        int inv = val == 1 ? 0 : 1;
        oneTree[treeSize + i] = node(1, val, val, val);
        zeroTree[treeSize + i] = node(1, inv, inv, inv);
    }

    for (int i = treeSize - 1; i > 0; i--) {
        oneTree[i] = merge(oneTree[2 * i], oneTree[2 * i + 1]);
        zeroTree[i] = merge(zeroTree[2 * i], zeroTree[2 * i + 1]);
    }

    for (int q = 0; q < m; q++) {
        // std::cout << "flipping index " << changes[q] << "\n";
        flipBit(oneTree, zeroTree, treeSize, changes[q]);

        // for (int i = 1; i < treeSize * 2; i++) {
        //     std::cout << oneTree[i].maxRun << " ";
        //
        //     if (i == treeSize - 1) {
        //         std::cout << "| ";
        //     }
        // }
        // std::cout << "\n";
        //
        // for (int i = 1; i < treeSize * 2; i++) {
        //     std::cout << zeroTree[i].maxRun << " ";
        //
        //     if (i == treeSize - 1) {
        //         std::cout << "| ";
        //     }
        // }
        // std::cout << "\n";

        std::cout << std::max(oneTree[1].maxRun, zeroTree[1].maxRun) << " ";
    }

    std::cout << "\n";
}
