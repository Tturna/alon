/*
You have n coins with positive integer values. The coins are numbered 1,2,...,n.
Your task is to process q queries of the form: "if you can use coins a ... b, what is
the smallest sum you cannot produce?"

Input

The first input line has two integers n and q: the number of coins and queries.
The second line has n integers x_1,x_2,...,x_n: the value of each coin.
Finally, there are q lines that describe the queries. Each line has two values a and b:
you can use coins a ... b.

Output

Print the answer for each query.

Constraints

1 <= n, q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n

Example
Input:
5 3
2 9 1 2 7
2 4
4 4
1 5

Output:
4
1
6

Explanation: First you can use coins [9,1,2], then coins [2] and finally coins [2,9,1,2,7].
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int getMinSum(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    int ref = 1;
    auto it = start;

    if (*it != 1) return ref;

    while (it <= end) {
        if (ref >= *it) {
            ref += *it;
            it++;
            continue;
        }

        break;
    }

    return ref;
}

int main() {
    // brute force

    int n, q;
    std::cin >> n >> q;

    std::vector<int> coins(n);

    for (int i = 0; i < n; i++) {
        std::cin >> coins[i];
    }

    std::vector<std::pair<int, int>> queries(q);
    std::string result;

    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a >> b;
        queries[i] = {a, b};

        auto copy = coins;
        auto start = copy.begin() + a - 1;
        auto end = copy.begin() + b - 1;
        std::sort(start, end + 1);

        result += std::to_string(getMinSum(start, end)) + "\n";
    }

    std::cout << result;
}
