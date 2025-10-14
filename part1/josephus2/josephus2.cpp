/*
Consider a game where there are n children (numbered 1,2,...,n) in a circle. During the game,
repeatedly k children are skipped and one child is removed from the circle. In which order will
the children be removed?

Input

The only input line has two integers n and k.

Output

Print n integers: the removal order.

Constraints

1 <= n <= 2 * 10^5
0 <= k <= 10^9

Example
Input:
7 2

Output:
3 6 2 7 5 1 4
*/

#include <iostream>
#include <vector>
int main() {
    unsigned long int n;
    unsigned long int k;
    std::cin >> n;
    std::cin >> k;

    std::vector<bool> kids;
    unsigned long int skips = k;
    unsigned long int i = 0;
    unsigned long int removed = 0;

    while (removed < n) {
        if (i >= n) i = 0;

        if (kids.size() < n) {
            kids.push_back(false);
        }

        auto kidRemoved = kids[i];

        if (kidRemoved) {
            i++;
            continue;
        }

        if (skips > 0) {
            skips--;
            i++;
            continue;
        }

        kidRemoved = true;
        removed++;
        std::cout << i + 1 << " ";
        i++;
        skips = k;
    }

    std::cout << "\n";
}
