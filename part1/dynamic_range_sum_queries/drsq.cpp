/*
Given an array of n integers, your task is to process q queries of the following types:

update the value at position k to u
what is the sum of values in range [a,b]?

Input

The first input line has two integers n and q: the number of values and queries.
The second line has n integers x_1,x_2,...,x_n: the array values.
Finally, there are q lines describing the queries. Each line has three integers: either "1 k u" or "2 a b".

Output

Print the result of each query of type 2.

Constraints

1 <= n,q <= 2 * 10^5
1 <= x_i, u <= 10^9
1 <= k <= n
1 <= a <= b <= n

Example
Input:
8 4
3 2 4 5 1 1 5 3
2 1 4
2 5 6
1 3 1
2 1 4

Output:
14
2
11
*/

#include <iostream>
#include <vector>

struct query {
    int type;
    long first;
    long second;
};

int main() {
    long n;
    long q;
    std::cin >> n;
    std::cin >> q;

    std::vector<long> arr;
    std::vector<query> queries;

    for (long i = 0; i < n; i++) {
        long val;
        std::cin >> val;
        arr.push_back(val);
    }

    for (long i = 0; i < q; i++) {
        int qtype;
        long qfirst;
        long qsecond;
        std::cin >> qtype;
        std::cin >> qfirst;
        std::cin >> qsecond;
        query q = { qtype, qfirst, qsecond };
        queries.push_back(q);
    }

    std::vector<long> tree(2 * n, 0);

    // insert leaf nodes into tree
    for (long i = 0; i < n; i++) {
        tree[n + i] = arr[i];
    }

    // build internal nodes
    for (long i = n - 1; i > 0; i--) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    // std::cout << "Segment tree: ";
    // for (auto val : tree) std::cout << val << " ";
    // std::cout << "\n";

    for (long i = 0; i < q; i++) {
        query qq = queries[i];

        // update first to second
        if (qq.type == 1) {
            long k = qq.first + n - 1;
            tree[k] = qq.second;

            for (k /= 2; k >= 1; k /= 2) {
                tree[k] = tree[2 * k] + tree[2 * k + 1];
            }
        }
        // sum from first to second
        else
        {
            long a = qq.first + n - 1;
            long b = qq.second + n - 1;
            long long s = 0;

            while (a <= b) {
                if (a % 2 == 1) s += tree[a++];
                if (b % 2 == 0) s += tree[b--];
                a /= 2;
                b /= 2;
            }

            std::cout << s << "\n";
        }
    }
}
