/*
Given an array of n integers, your task is to find for each array position the nearest
position to its left having a smaller value.

Input

The first input line has an integer n: the size of the array.
The second line has n integers x_1,x_2,...,x_n: the array values.

Output

Print n integers: for each array position the nearest position with a smaller value.
If there is no such position, print 0.

Constraints

1 <= n <= 2 * 10^5
1 <= x_i <= 10^9

Example
Input:
8
2 5 1 4 8 3 2 5

Output:
0 1 0 3 4 3 3 7
*/

#include <iostream>
#include <vector>
int main() {
    int n;
    std::cin >> n;
    int vals[n];

    for (int i = 0; i < n; i++) {
        std::cin >> vals[i];
    }

    std::vector<int> idxs;

    for (int i = 0; i < n; i++) {
        if (idxs.size() == 0) {
            std::cout << 0 << " ";
            idxs.push_back(i);
            continue;
        }

        auto it = idxs.end() - 1;

        while (vals[*it] >= vals[i]) {
            idxs.pop_back();
            it = idxs.end() - 1;

            if (idxs.size() == 0) break;
        }

        if (idxs.size() == 0) {
            std::cout << 0 << " ";
            idxs.push_back(i);
            continue;
        }

        std::cout << ((*it) + 1) << " ";
        idxs.push_back(i);
    }

    std::cout << "\n";
}
