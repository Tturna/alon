/*
You are given an array containing n positive integers.
Your task is to divide the array into k subarrays so that the maximum sum in a subarray
is as small as possible.

Input

The first input line contains two integers n and k: the size of the array and the number of
subarrays in the division.
The next line contains n integers x_1,x_2,...,x_n: the contents of the array.

Output
Print one integer: the maximum sum in a subarray in the optimal division.
Constraints

1 <= n <= 2 * 10^5
1 <= k <= n
1 <= x_i <= 10^9

Example
Input:
5 3
2 4 7 3 5

Output:
8

Explanation: An optimal division is [2,4],[7],[3,5] where the sums of the subarrays are
6,7,8. The largest sum is the last sum 8.
*/

#include <iostream>
#include <vector>

bool can_make_subarrays(long long sumLimit, const std::vector<long long>& arr, long long k) {
    long long subarrSum = 0;
    long long cuts = 0;

    for (unsigned long i = 0; i < arr.size(); i++) {
        if (arr[i] > sumLimit) return false;

        if (subarrSum + arr[i] > sumLimit) {
            cuts++;
            subarrSum = arr[i];

            if (cuts == k) return false;
            continue;
        }

        subarrSum += arr[i];
    }

    return true;
}

int main() {
    int n;
    int k;
    std::cin >> n;
    std::cin >> k;

    std::vector<long long> arr;
    long long maxSum = 0;

    for (int i = 0; i < n; i++) {
        long long val;
        std::cin >> val;
        arr.push_back(val);
        maxSum += val;
    }

    long long min = 1;
    long long max = maxSum;

    while (min < max) {
        long long mid = (min + max) / 2;

        if (can_make_subarrays(mid, arr, k)) {
            max = mid;
        }
        else {
            min = mid + 1;
        }
    }

    std::cout << min << "\n";
}
