/*
Given n integers, your task is to report for each integer the number of its divisors.
For example, if x=18, the correct answer is 6 because its divisors are 1,2,3,6,9,18.

Input

The first input line has an integer n: the number of integers.
After this, there are n lines, each containing an integer x.

Output

For each integer, print the number of its divisors.

Constraints

1 <= n <= 10^5
1 <= x <= 10^6

Example
Input:
3
16
17
18

Output:
5
2
6
*/

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n;

    std::cin >> n;

    std::vector<int> inputs;
    int maxInput = 0;

    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;

        inputs.push_back(val);
        maxInput = std::max(maxInput, val);
    }

    std::vector<int> sieve(maxInput + 1, 0);
    sieve[1] = 1;

    for (int i = 2; i <= maxInput; i++) {
        sieve[i] = 2;
    }

    for (int i = 2; i <= maxInput; i++) {
        // if (sieve[i]) continue;
        for (int j = 2*i; j <= maxInput; j += i) {
            sieve[j]++;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << sieve[inputs[i]] << "\n";
    }
}
