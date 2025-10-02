/*
Consider a game where there are n children (numbered 1,2,...,n) in a circle. During the game,
every other child is removed from the circle until there are no children left. In which order
will the children be removed?

Input

The only input line has an integer n.

Output

Print n integers: the removal order.

Constraints

1 <= n <= 2 * 10^5

Example
Input:
7

Output:
2 4 6 1 5 3 7
*/

#include <iostream>
#include <utility>
#include <vector>
int main() {
    unsigned long int n;
    std::cin >> n;
    std::vector<std::pair<unsigned long int, bool>> children;
    bool shouldRemove = false;
    unsigned long int i = 0;
    unsigned long int removedCount = 0;

    while (removedCount < n) {
        if (children.size() < n) {
            children.push_back({i, shouldRemove});
        }
        else if (children[i].second) {
            i++;
            if (i >= n) i = 0;
            continue;
        }

        if (shouldRemove) {
            children[i].second = true;
            removedCount++;
            std::cout << (i + 1) << " ";
        }

        shouldRemove = !shouldRemove;

        i++;
        if (i >= n) i = 0;
    }

    std::cout << "\n";
}
