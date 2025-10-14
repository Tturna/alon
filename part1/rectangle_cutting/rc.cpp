/*
Given an a * b rectangle, your task is to cut it into squares. On each move you can select
a rectangle and cut it into two rectangles in such a way that all side lengths remain integers.
What is the minimum possible number of moves?

Input

The only input line has two integers a and b.

Output

Print one integer: the minimum number of moves.

Constraints

1 <= a,b <= 500

Example
Input:
3 5

Output:
3
*/

#include <iostream>
int main() {
    int x;
    int y;
    std::cin >> x;
    std::cin >> y;
    int steps = 0;

    // Greedy algorithm for splitting into squares
    while (x != y) {
        steps++;

        if (x > y) {
            x -= y;
        }
        else {
            y -= x;
        }
    }

    std::cout << steps << "\n";
}
