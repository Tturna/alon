#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct node {
    std::vector<long long> v;   // sorted values
    std::vector<long long> pref; // prefix sums
};

int n, q;
std::vector<long long> a;
std::vector<node> seg;

node mergeNode(node& left, node& right) {
    node res;
    res.v.resize(left.v.size() + right.v.size());
    std::merge(left.v.begin(), left.v.end(), right.v.begin(), right.v.end(), res.v.begin());
    res.pref.resize(res.v.size());

    if (!res.v.empty()) {
        res.pref[0] = res.v[0];

        for (int i = 1; i < (int)res.v.size(); i++)
            res.pref[i] = res.pref[i - 1] + res.v[i];
    }
    return res;
}

void build(int idx, int l, int r) {
    if (l == r) {
        seg[idx].v = {a[l]};
        seg[idx].pref = {a[l]};
        return;
    }

    int m = (l + r) / 2;
    build(idx * 2, l, m);
    build(idx * 2 + 1, m + 1, r);
    seg[idx] = mergeNode(seg[idx * 2], seg[idx * 2 + 1]);
}

void queryNodes(int idx, int l, int r, int ql, int qr, std::vector<int> &nodes) {
    if (qr < l || r < ql) return;

    if (ql <= l && r <= qr) {
        nodes.push_back(idx);
        return;
    }

    int m = (l + r) / 2;
    queryNodes(idx * 2, l, m, ql, qr, nodes);
    queryNodes(idx * 2 + 1, m + 1, r, ql, qr, nodes);
}

int main() {
    std::cin >> n >> q;
    a.resize(n);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    seg.resize(4*n);
    build(1, 0, n-1);

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--; r--;

        std::vector<int> nodes;
        queryNodes(1, 0, n - 1, l, r, nodes);

        struct item {
            long long val;
            int node, idx;
            bool operator>(item const &o) const { return val > o.val; }
        };

        // Min-heap to merge sorted lists
        std::priority_queue<item, std::vector<item>, std::greater<item>> pq;

        for (int ni : nodes) {
            if (!seg[ni].v.empty()) {
                pq.push({seg[ni].v[0], ni, 0});
            }
        }

        long long reach = 0;

        while (!pq.empty()) {
            auto [val, nd, pos] = pq.top();
            if (val > reach + 1) break;
            pq.pop();

            reach += val;

            if (pos + 1 < (int)seg[nd].v.size())
                pq.push({seg[nd].v[pos + 1], nd, pos + 1});
        }

        std::cout << reach + 1 << "\n";
    }

    return 0;
}
