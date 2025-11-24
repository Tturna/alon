/*
Given n ranges, your task is to count for each range how many other ranges it contains
and how many other ranges contain it.
Range [a,b] contains range [c,d] if a <= c and d <= b.

Input

The first input line has an integer n: the number of ranges.
After this, there are n lines that describe the ranges. Each line has two integers x
and y: the range is [x,y].
You may assume that no range appears more than once in the input.

Output

First print a line that describes for each range (in the input order) how many other ranges it contains.
Then print a line that describes for each range (in the input order) how many other ranges contain it.

Constraints

1 <= n <= 2 * 10^5
1 <= x < y <= 10^9

Example
Input:
4
1 6
2 4
4 8
3 6

Output:
2 0 0 0
0 1 0 1
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class segmentTree {
private:
    std::vector<int> tree;
    int size;
    
    void update(int node, int node_left, int node_right, int pos, int value) {
        if (node_left == node_right) {
            tree[node] += value;
            return;
        }
        int mid = (node_left + node_right) / 2;
        if (pos <= mid) {
            update(2 * node, node_left, mid, pos, value);
        } else {
            update(2 * node + 1, mid + 1, node_right, pos, value);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    int query(int node, int node_left, int node_right, int query_left, int query_right) {
        if (query_left > node_right || query_right < node_left) {
            return 0;
        }
        if (query_left <= node_left && node_right <= query_right) {
            return tree[node];
        }
        int mid = (node_left + node_right) / 2;
        return query(2 * node, node_left, mid, query_left, query_right) +
               query(2 * node + 1, mid + 1, node_right, query_left, query_right);
    }
    
public:
    segmentTree(int n) : size(n) {
        tree.assign(4 * n, 0);
    }
    
    void update(int pos, int value) {
        update(1, 0, size - 1, pos, value);
    }
    
    int query(int left, int right) {
        if (left > right) return 0;
        return query(1, 0, size - 1, left, right);
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::pair<int, int>> ranges(n);

    for (int i = 0; i < n; i++) {
        std::cin >> ranges[i].first >> ranges[i].second;
    }
    
    // coordinate compression
    std::vector<int> coords;

    for (int i = 0; i < n; i++) {
        coords.push_back(ranges[i].second);
    }

    std::sort(coords.begin(), coords.end());
    coords.erase(std::unique(coords.begin(), coords.end()), coords.end());
    
    std::map<int, int> compress;

    for (int i = 0; i < (int)coords.size(); i++) {
        compress[coords[i]] = i;
    }
    
    std::vector<int> contains_count(n);
    std::vector<int> contained_by_count(n);
    
    // Sort by start ascending, then by end descending
    // Process in reverse order
    std::vector<int> indices(n);
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    std::sort(indices.begin(), indices.end(), [&](int i, int j) {
        if (ranges[i].first != ranges[j].first) {
            return ranges[i].first < ranges[j].first;
        }
        return ranges[i].second > ranges[j].second;
    });
    
    segmentTree tree1(coords.size());

    for (int i = n - 1; i >= 0; i--) {
        int idx = indices[i];
        int end_compressed = compress[ranges[idx].second];
        // count ranges with end <= current end (will be processed later, have start >= current start)
        contains_count[idx] = tree1.query(0, end_compressed);
        tree1.update(end_compressed, 1);
    }
    
    // sort by start descending, then by end ascending
    // Process in reverse order
    std::sort(indices.begin(), indices.end(), [&](int i, int j) {
        if (ranges[i].first != ranges[j].first) {
            return ranges[i].first > ranges[j].first;
        }
        return ranges[i].second < ranges[j].second;
    });
    
    segmentTree tree2(coords.size());

    for (int i = n - 1; i >= 0; i--) {
        int idx = indices[i];
        int end_compressed = compress[ranges[idx].second];
        contained_by_count[idx] = tree2.query(end_compressed, coords.size() - 1);
        tree2.update(end_compressed, 1);
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << contains_count[i];
        if (i < n - 1) std::cout << " ";
    }

    std::cout << "\n";
    
    for (int i = 0; i < n; i++) {
        std::cout << contained_by_count[i];
        if (i < n - 1) std::cout << " ";
    }
    std::cout << "\n";
}
