/*
You are given an array of n positive integers. Your task is to find two integers such that
their greatest common divisor is as large as possible.

Input

The first input line has an integer n: the size of the array.
The second line has n integers x_1,x_2,...,x_n: the contents of the array.

Output

Print the maximum greatest common divisor.

Constraints

2 <= n <= 2 * 10^5
1 <= x_i <= 10^6

Example
Input:
5
3 14 15 7 9

Output:
7
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vals;
    int maxVal = 0;

    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        vals.push_back(val);
        maxVal = std::max(maxVal, val);
    }

    std::vector<int> existing(maxVal + 1, 0);

    for (int i = 0; i < n; i++) {
        // increment instead of setting to 1 so that duplicate input values get >1 as their value.
        // When the loop below encounters this number, it will be considered a common divisor.
        existing[vals[i]]++;
    }

    for (int i = maxVal; i >= 1; i--) {
        int multiples = 0;
        for (int j = i; j <= maxVal; j += i) {
            multiples += existing[j];
        }

        if (multiples >= 2) {
            std::cout << i << "\n";
            break;
        }
    }
}
