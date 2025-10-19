/*
You are given an array of n numbers. In how many ways can you choose a subset of
the numbers with sum x?

Input

The first input line has two numbers n and x: the array size and the required sum.
The second line has n integers t_1,t_2,...,t_n: the numbers in the array.

Output

Print the number of ways you can create the sum x.

Constraints

1 <= n <= 40
1 <= x <= 10^9
1 <= t_i <= 10^9

Example
Input:
4 5
1 2 3 2

Output:
3
*/

#include <algorithm>
#include <iostream>
#include <vector>

void get_valid_subset_sums(unsigned int k, const std::vector<int>& set, std::vector<long long>& sums,
    std::vector<int>& selections
) {
    if (k == set.size()) {
        long sum = 0;

        for (unsigned int i = 0; i < k; i++) {
            if (selections[i] == 1) {
                sum += set[i];
            }
        }

        sums.push_back(sum);
    }
    else {
        selections[k] = 0;
        get_valid_subset_sums(k + 1, set, sums, selections);
        selections[k] = 1;
        get_valid_subset_sums(k + 1, set, sums, selections);
    }
}

int main() {
    int n;
    int x;
    std::cin >> n;
    std::cin >> x;

    std::vector<int> vals1;
    std::vector<int> vals2;

    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;

        if (i < n / 2) {
            vals1.push_back(val);
        }
        else {
            vals2.push_back(val);
        }
    }

    std::vector<long long> sums1;
    std::vector<long long> sums2;
    std::vector<int> selections(n);

    get_valid_subset_sums(0, vals1, sums1, selections);
    selections = std::vector<int>(n);
    get_valid_subset_sums(0, vals2, sums2, selections);

    // long ans = 0;
    //
    // for (unsigned long i = 0; i < sums1.size(); i++) {
    //     for (unsigned long j = 0; j < sums2.size(); j++) {
    //         if (sums1[i] == x - sums2[j]) {
    //             ans++;
    //         }
    //     }
    // }

    std::sort(sums2.begin(), sums2.end());

    long long ans = 0;
    for (auto s1 : sums1) {
        long long target = x - s1;
        auto range = std::equal_range(sums2.begin(), sums2.end(), target);
        ans += range.second - range.first;
    }

    std::cout << ans << "\n";
}
