/*
Find the middle element when the numbers in an n * n multiplication table are sorted in
increasing order. It is assumed that n is odd. For example, the 3 * 3 multiplication
table is as follows:
[
    1, 2, 3
    2, 4, 6
    3, 6, 9
]

The numbers in increasing order are [1,2,2,3,3,4,6,6,9], so the answer is 3.

Input

The only input line has an integer n.

Output

Print one integer: the answer to the task.

Constraints

1 <= n < 10^6

Example
Input:
3

Output:
3
*/

#include <algorithm>
#include <iostream>
int main() {
    long long n;
    std::cin >> n;

    // mult table has n * n elements. The median is at index (n * n) / 2 if it's 0-indexed,
    // meaning there are (n * n + 1) / 2 elements less than or equal to the median.
    // The median is the smallest value in the table that has (n * n + 1) / 2 elements
    // less than or equal to it.
    // f(x) >= (n * n + 1) / 2

    long long low = 1;
    long long high = n * n;

    while (low < high) {
        long long mid = (low + high) / 2;
        long long sum = 0;

        // for every row, count how many values are <= to x.
        // for row i, every value that's i or higher is counted.
        // that happens to be x / i or n if x / i is larger than row size.
        for (long long i = 1; i <= n; i++) {
            sum += std::min(n, mid / i);
        }

        if (sum >= (n * n + 1) / 2) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }

    std::cout << high << "\n";
}
