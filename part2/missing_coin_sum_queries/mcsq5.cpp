#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct query {
    int l, r, idx, block;
    bool operator<(const query &other) const {
        if (block != other.block) return block < other.block;
        return (block & 1) ? (r > other.r) : (r < other.r);
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    // compress values
    std::vector<long long> sorted_vals = a;
    std::sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(std::unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());

    int m = sorted_vals.size();
    std::vector<int> comp(n);

    for (int i = 0; i < n; i++) {
        comp[i] = std::lower_bound(sorted_vals.begin(), sorted_vals.end(), a[i]) - sorted_vals.begin();
    }

    // prepare Mo's queries
    int block_size = std::max(1, (int)std::sqrt(n));
    std::vector<query> queries(q);

    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--; r--;
        queries[i] = {l, r, i, l / block_size};
    }
    std::sort(queries.begin(), queries.end());

    // frequency + buckets
    std::vector<long long> freq(m, 0);

    int bucketSize = std::sqrt(m) + 1;
    int num_buckets = (m + bucketSize - 1) / bucketSize;

    std::vector<long long> bucket_sum(num_buckets, 0);   // sum of values * freq
    std::vector<long long> bucket_count(num_buckets, 0); // count of occurrences

    auto add = [&](int pos) {
        int v = comp[pos];
        int bucketId = v / bucketSize;
        freq[v]++;
        bucket_sum[bucketId] += sorted_vals[v];
        bucket_count[bucketId]++;
    };

    auto remove = [&](int pos) {
        int v = comp[pos];
        int bucketId = v / bucketSize;
        freq[v]--;
        bucket_sum[bucketId] -= sorted_vals[v];
        bucket_count[bucketId]--;
    };

    // compute smallest missing sum for current freq
    auto smallest_missing = [&]() {
        long long reach = 0;

        for (int b = 0; b < num_buckets; b++) {
            if (bucket_sum[b] == 0) continue;

            if (bucket_sum[b] <= reach) {
                reach += bucket_sum[b];
            } else {
                // need to inspect individual values inside bucket
                int start = b * bucketSize;
                int end = std::min(m, start + bucketSize);

                for (int i = start; i < end; i++) {
                    if (freq[i] == 0) continue;

                    long long val = sorted_vals[i];

                    // If val > reach + 1, we found the gap
                    if (val > reach + 1) return reach + 1;

                    // Otherwise we can extend reach
                    reach += val * freq[i];
                }
            }
        }

        return reach + 1;
    };

    std::vector<long long> answers(q);

    int curL = 0, curR = -1;

    for (auto& qry : queries) {
        int L = qry.l;
        int R = qry.r;

        while (curL > L) add(--curL);
        while (curR < R) add(++curR);
        while (curL < L) remove(curL++);
        while (curR > R) remove(curR--);

        answers[qry.idx] = smallest_missing();
    }

    for (int i = 0; i < q; i++) {
        std::cout << answers[i] << "\n";
    }
}
