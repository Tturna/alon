#include <algorithm>
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
        tree[i] = std::min(tree[2 * i], tree[2 * i + 1]);
    }

    for (long i = 0; i < q; i++) {
        query qq = queries[i];

        // update first to second
        if (qq.type == 1) {
            long k = qq.first + n - 1;
            tree[k] = qq.second;

            for (k /= 2; k >= 1; k /= 2) {
                tree[k] = std::min(tree[2 * k], tree[2 * k + 1]);
            }
        }
        // minimum from first to second
        else
        {
            long a = qq.first + n - 1;
            long b = qq.second + n - 1;
            long x = tree[a];

            while (a <= b) {
                if (a % 2 == 1) x = std::min(x, tree[a++]);
                if (b % 2 == 0) x = std::min(x, tree[b--]);
                a /= 2;
                b /= 2;
            }

            std::cout << x << "\n";
        }
    }
}
