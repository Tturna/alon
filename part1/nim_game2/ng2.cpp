/*
There are n heaps of sticks and two players who move alternately. On each move, a
player chooses a non-empty heap and removes 1, 2, or 3 sticks. The player who removes
the last stick wins the game. Your task is to find out who wins if both players play optimally.

Input

The first input line contains an integer t: the number of tests. After this, t test cases
are described: The first line contains an integer n: the number of heaps.
The next line has n integers x_1,x_2,...,x_n: the number of sticks in each heap.

Output

For each test case, print "first" if the first player wins the game and "second" if
the second player wins the game.

Constraints

1 <= t <= 2 * 10^5
1 <= n <= 2 * 10^5
1 <= x_i <= 10^9
the sum of all n is at most 2 * 10^5

Example
Input:
3
4
5 7 2 5
2
4 1
3
4 4 4

Output:
first
first
second
*/

#include <iostream>
#include <string>

int main() {
    int testCount;
    std::cin >> testCount;

    // xor = exclusive or = true only when operands are different.
    // xor sum = xor for a set of values, e.g. xor sum for [2, 5, 7, 3] = 2 XOR 5 XOR 7 XOR 3
    // when xor sum = 0, you lose. Otherwise you win.

    std::string result;

    for (int i = 0; i < testCount; i++) {
        int heapCount;
        std::cin >> heapCount;
        int xorSum;
        std::cin >> xorSum;
        xorSum %= 4;

        for (int j = 1; j < heapCount; j++) {
            int heapSize;
            std::cin >> heapSize;
            xorSum ^= heapSize % 4;
        }

        result += xorSum == 0 ? "second\n" : "first\n";
    }

    std::cout << result;
}
