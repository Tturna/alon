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
#include <unordered_map>

int main() {
    unsigned int n;
    unsigned int k;
    std::cin >> n;
    std::cin >> k;

    unsigned long int arr[n];

    for (unsigned int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::unordered_map<unsigned long int, unsigned long int> distincts;
    unsigned int left = 0;
    unsigned int right = 0;
    unsigned long int subarrays = 0;

    while (left < n - 1) {
        unsigned long int rightVal = arr[right];

        if (right == n || (distincts.size() == k && distincts.find(rightVal) == distincts.end())) {
            unsigned long int leftVal = arr[left];

            while (distincts.size() >= k) {
                distincts[leftVal]--;
                if (distincts[leftVal] == 0) distincts.erase(leftVal);
                left++;
                leftVal = arr[left];
                subarrays++;
            }

            continue;
        }
        
        subarrays++;
        distincts[rightVal]++;
        right++;
    }

    std::cout << subarrays << "\n";
}
