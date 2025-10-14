/*
Given an array of n integers, your task is to calculate the number of subarrays that have at
most k distinct values.

Input

The first input line has two integers n and k.
The next line has n integers x_1,x_2,...,x_n: the contents of the array.

Output

Print one integer: the number of subarrays.

Constraints

1 <= k <= n <= 2 * 10^5
1 <= x_i <= 10^9

Example
Input:
5 2
1 2 3 1 1

Output:
10
*/

#include <iostream>
#include <set>

int main() {
    unsigned int n;
    unsigned int k;
    std::cin >> n;
    std::cin >> k;

    unsigned long int arr[n];

    for (unsigned int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::set<unsigned long int> asd;
    unsigned long int subarrays = 0;

    for (unsigned int i = 0; i < n; i++) {
        asd.clear();
        asd.insert(arr[i]);
        subarrays++;

        for (unsigned int j = i + 1; j < n; j++) {
            if (asd.find(arr[j]) == asd.end() && asd.size() >= k) {
                break;
            }

            asd.insert(arr[j]);
            subarrays++;
        }
    }

    std::cout << subarrays << "\n";
}
