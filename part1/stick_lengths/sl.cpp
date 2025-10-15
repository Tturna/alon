/*
There are n sticks with some lengths. Your task is to modify the sticks so that each stick
has the same length. You can either lengthen and shorten each stick. Both operations cost
x where x is the difference between the new and original length.
What is the minimum total cost?

Input

The first input line contains an integer n: the number of sticks.
Then there are n integers: p_1,p_2,===,p_n: the lengths of the sticks.

Output

Print one integer: the minimum total cost.

Constraints

1 <= n <= 2 * 10^5
1 <= p_i <= 10^9

Example
Input:
5
2 3 1 5 2

Output:
5
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    unsigned long int n;
    std::cin >> n;
    std::vector<unsigned long int> sticks;

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int h;
        std::cin >> h;
        sticks.push_back(h);
    }

    // Better to use a vector that we sort after input.
    // A multiset wouldn't require sorting but you can't access the middle value by index.
    // Multiset sorting + linear access boils down to a higher complexity than just
    // O(n log n) for vector sort + constant value lookup.
    std::sort(sticks.begin(), sticks.end());

    unsigned long int median = 0;
    unsigned long int total = 0;
    median = sticks[n / 2];

    for (unsigned long int i = 0; i < n; i++) {
        auto h = sticks[i];

        // Can't just do abs(h - median) because we use unsigned values
        if (h > median) {
            total += (h - median);
        }
        else {
            total += (median - h);
        }
    }

    std::cout << total << "\n";
}
