/*
You are given an array containing n integers. Your task is to determine the longest
increasing subsequence in the array, i.e., the longest subsequence where every element is
larger than the previous one.
A subsequence is a sequence that can be derived from the array by deleting some elements
without changing the order of the remaining elements.

Input

The first line contains an integer n: the size of the array.
After this there are n integers x_1,x_2,...,x_n: the contents of the array.

Output

Print the length of the longest increasing subsequence.

Constraints

1 <= n <= 2 * 10^5
1 <= x_i <= 10^9

Example
Input:
8
7 3 5 3 6 2 9 8

Output:
4
*/

#include <iostream>
#include <vector>
int main() {
    long n;
    std::cin >> n;

    std::vector<long> tails(1);
    std::cin >> tails[0];

    for (long i = 1; i < n; i++) {
        long val;
        std::cin >> val;

        unsigned long min = 0;
        unsigned long max = tails.size();

        while (min < max) {
            long mid = (min + max) / 2;

            if (tails[mid] < val) {
                min = mid + 1;
            }
            else {
                max = mid;
            }
        }

        if (min >= tails.size()) {
            tails.push_back(val);
        }
        else {
            tails[min] = val;
        }
    }

    std::cout << tails.size() << "\n";
}
