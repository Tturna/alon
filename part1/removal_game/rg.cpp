/*
There is a list of n numbers and two players who move alternately. On each move, a player
removes either the first or last number from the list, and their score increases by that number.
Both players try to maximize their scores.

What is the maximum possible score for the first player when both players play optimally?

Input

The first input line contains an integer n: the size of the list.
The next line has n integers x_1,x_2,...,x_n: the contents of the list.

Output

Print the maximum possible score for the first player.

Constraints

1 <= n <= 5000
-10^9 <= x_i <= 10^9

Example
Input:
4
4 5 1 3

Output:
8
*/

#include <algorithm>
#include <iostream>

long long sum(long long* x, int left, int right) {
    long long sum = 0;

    for (int i = left; i <= right; i++) {
        sum += x[i];
    }

    return sum;
}

long long getOptimal(long long* x, int left, int right) {
    if (right == 0) {
        return x[0];
    }

    if (left + 1 == right) {
        return std::max(x[left], x[right]);
    }

    long long leftChoice = x[left] + sum(x, left + 1, right) - getOptimal(x, left + 1, right);
    long long rightChoice = x[right] + sum(x, left, right - 1) - getOptimal(x, left, right - 1);

    return std::max(leftChoice, rightChoice);
}

int main() {
    int n;
    std::cin >> n;
    long long x[n];

    for (long long i = 0; i < n; i++) {
        std::cin >> x[i];
    }

    /*
    x[1, 2, 3]
    opt = max(
        1 + sum([2, 3]) - opt from [2, 3]

        3 + sum([1, 2]) - opt from [1, 2]
    )
    */

    long long answer = getOptimal(x, 0, n - 1);
    std::cout << answer << "\n";
}
