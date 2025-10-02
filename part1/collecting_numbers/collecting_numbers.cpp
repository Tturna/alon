/*
You are given an array that contains each number between 1...n exactly once.
Your task is to collect the numbers from 1 to n in increasing order.
On each round, you go through the array from left to right and collect as many numbers as possible.
What will be the total number of rounds?

Input

The first line has an integer n: the array size.
The next line has n integers x_1,x_2,\dots,x_n: the numbers in the array.

Output

Print one integer: the number of rounds.

Constraints

1 <= n <= 2 * 10^5

Example
Input:
5
4 2 1 5 3

Output:
3
*/

#include <iostream>
#include <vector>

int main() {
    unsigned long int n;
    std::cin >> n;

    unsigned long int rounds = 1;
    std::vector<unsigned long int> arr(n);

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int x;
        std::cin >> x;

        // Store index of given integer, essentially flipping the values and indexes
        // of the array from the intuitive. This way the positions of the array values
        // can be compared easily.
        arr[x - 1] = i;
    }

    for (unsigned long int i = 0; i < n - 1; i++) {
        unsigned long int smallIndex = arr[i];
        unsigned long int bigIndex = arr[i + 1];

        // Compare index of value i against index of value i + 1.
        // Every time the index of the next number is smaller, a new round
        // is needed.
        if (smallIndex > bigIndex) rounds++;
    }

    std::cout << rounds << "\n";
}
