/*
You have n coins with positive integer values. What is the smallest sum you cannot create using
a subset of the coins?

Input

The first line has an integer n: the number of coins.
The second line has n integers x_1,x_2,...,x_n: the value of each coin.

Output

Print one integer: the smallest coin sum.

Constraints

1 <= n <= 2 * 10^5
1 <= x_i <= 10^9

Example
Input:
5
2 9 1 2 7

Output:
6
*/

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    unsigned long int n;
    std::vector<unsigned long int> coins;

    std::cin >> n;

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int val;
        std::cin >> val;
        coins.push_back(val);
    }

    std::sort(coins.begin(), coins.end());
    unsigned long int ref = 1;

    if (coins[0] == 1) {
        ref += coins[0];

        for (unsigned long int i = 1; i < n; i++) {
            if (ref >= coins[i]) {
                ref += coins[i];
                continue;
            }
            else if (ref < coins[i]) {
                break;
            }
        }
    }

    std::cout << ref << "\n";
}
