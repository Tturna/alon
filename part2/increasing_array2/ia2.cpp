/*
You are given an array of n integers. You want to modify the array so that it is
increasing, i.e., every element is at least as large as the previous element.
On each move, you can increase or decrease the value of any element by one. What is
the minimum number of moves required?

Input

The first input line contains an integer n: the size of the array.
Then, the second line contains n integers x_1,x_2,...,x_n: the contents of the array.

Output

Print the minimum number of moves.

Constraints

1 <= n <= 2 * 10^5
1 <= x_i <= 10^9

Example
Input:
5
3 8 5 6 5

Output:
4
*/

#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <utility>

struct block {
    std::multiset<long long> vals;
    std::multiset<long long>::iterator med;

    block(long long x) {
        vals.insert(x);
        med = vals.begin();
    }
};

void add(block& bl, long long x) {
    // Insert and update median iterator
    if (bl.vals.empty()) {
        bl.vals.insert(x);
        bl.med = bl.vals.begin();
        return;
    }

    bl.vals.insert(x);

    // Update median pointer
    if (x >= *bl.med) {
        if (bl.vals.size() % 2 == 0) {
            // size even, median should move left
            bl.med--;
        }
    } else {
        if (bl.vals.size() % 2 == 1) {
            // size odd, median should move right
            bl.med++;
        }
    }
}

void merge(block& a, block& b) {
    // Always merge smaller set into larger one
    if (b.vals.size() > a.vals.size()) {
        swap(a.vals, b.vals);
        swap(a.med, b.med);
    }

    for (long long x : b.vals) {
        add(a, x);
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

    for (long long x : arr) {
        blocks.emplace_back(x);

        // Merge while violating non-decreasing medians
        while (blocks.size() >= 2 &&
           *blocks[blocks.size() - 2].med > *blocks[blocks.size() - 1].med)
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
        long long m = *b.med;

        for (int i = 0; i < b.vals.size(); i++) {
            total += llabs(arr[idx] - m);
            idx++;
        }
    }

    std::cout << total << "\n";
}
