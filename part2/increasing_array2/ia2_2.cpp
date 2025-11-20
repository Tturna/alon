#include <iostream>
#include <queue>
#include <vector>

struct block {
    std::priority_queue<long long> low; // max-heap
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> high; // min-heap

    int size;

    block(long long x) : size(1) {
        // start with one element, median lives in low
        low.push(x);
    }

    long long median() const {
        return low.top();
    }
};

void rebalance(block& b) {
    if (b.low.size() > b.high.size() + 1) {
        long long x = b.low.top();
        b.low.pop();
        b.high.push(x);
    }
    else if (b.high.size() > b.low.size()) {
        long long x = b.high.top();
        b.high.pop();
        b.low.push(x);
    }
}

void add(block& b, long long x) {
    if (b.size == 0) {
        b.low.push(x);
        b.size = 1;
        return;
    }

    if (x <= b.median()) {
        b.low.push(x);
    } else {
        b.high.push(x);
    }

    b.size++;
    rebalance(b);
}

void merge(block& a, block& b) {
    // merge smaller into larger
    if (b.size > a.size) {
        std::swap(a.low, b.low);
        std::swap(a.high, b.high);
        std::swap(a.size, b.size);
    }

    // move all elements of b into a
    while (!b.low.empty()) {
        add(a, b.low.top());
        b.low.pop();
    }
    while (!b.high.empty()) {
        add(a, b.high.top());
        b.high.pop();
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::vector<block> blocks;
    blocks.reserve(n);

    for (long long x : arr) {
        blocks.emplace_back(x);

        // merge while breaking monotonic medians
        while (blocks.size() >= 2 &&
           blocks[blocks.size()-2].median() > blocks[blocks.size()-1].median())
        {
            block b = std::move(blocks.back());
            blocks.pop_back();

            block& a = blocks.back();
            merge(a, b);
        }
    }

    long long total = 0;
    int idx = 0;

    for (auto& b : blocks) {
        long long m = b.median();

        for (int i = 0; i < b.size; i++) {
            total += llabs(arr[idx] - m);
            idx++;
        }
    }

    std::cout << total << "\n";
}
