/*
Given an array of n integers, your task is to process q queries of the following types:

increase each value in range [a,b] by u
what is the value at position k?

Input

The first input line has two integers n and q: the number of values and queries.
The second line has n integers x_1,x_2,...,x_n: the array values.
Finally, there are q lines describing the queries. Each line has three integers: either "1 a b u" or "2 k".

Output

Print the result of each query of type 2.

Constraints

1 <= n,q <= 2 * 10^5
1 <= x_i, u <= 10^9
1 <= k <= n
1 <= a <= b <= n

Example
Input:
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4

Output:
5
6
*/

#include <iostream>
#include <vector>

void addToRange(std::vector<long>& lazyAdditionsTree, long treeSize, int leftIndex,
    int rightIndex, long valueToAdd
) {
    int left = leftIndex + treeSize - 1;
    int right = rightIndex + treeSize;

    while (left < right) {
        if (left % 2 == 1) {
            lazyAdditionsTree[left] += valueToAdd;
            left++;
        }

        if (right % 2 == 1) {
            right--;
            lazyAdditionsTree[right] += valueToAdd;
        }

        left /= 2;
        right /= 2;
    }
};

long queryAtIndex(std::vector<long>& lazyAdditionsTree, std::vector<long>& baseValues,
    long treeSize, int position
) {
    int treeIndex = position + treeSize - 1;

    long totalAddition = 0;

    while (treeIndex > 0) {
        totalAddition += lazyAdditionsTree[treeIndex];
        treeIndex /= 2;
    }

    return baseValues[position - 1] + totalAddition;
};


int main() {
    long n;
    long q;

    std::cin >> n;
    std::cin >> q;

    std::vector<long> baseValues(n);

    for (int i = 0; i < n; i++) {
        std::cin >> baseValues[i];
    }

    long treeSize = 1;

    while (treeSize < n) {
        treeSize *= 2;
    }

    std::vector<long> lazyAdditionsTree(2 * treeSize, 0);

    for (int i = 0; i < q; i++) {
        int queryType;
        std::cin >> queryType;

        if (queryType == 1) {
            int left, right;
            long increaseBy;
            std::cin >> left >> right >> increaseBy;

            addToRange(lazyAdditionsTree, treeSize, left, right, increaseBy);
        } 
        else if (queryType == 2) {
            int index;
            std::cin >> index;
            std::cout << queryAtIndex(lazyAdditionsTree, baseValues, treeSize, index) << " ";
        }
    }

    std::cout << "\n";
}
