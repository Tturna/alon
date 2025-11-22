/*
You are given an array of n integers and q queries of the form: how many distinct values are
there in a range [a,b]?

Input

The first input line has two integers n and q: the array size and number of queries.
The next line has n integers x_1,x_2,...,x_n: the array values.
Finally, there are q lines describing the queries. Each line has two integers a and b.

Output

For each query, print the number of distinct values in the range.

Constraints

1 <= n,q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n

Example
Input:
5 3
3 2 3 1 2
1 3
2 4
1 5

Output:
2
3
3
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
            tree[node] = value;
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

struct query {
    int left;
    int right;
    int index;
};

int main() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> arr(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> arr[i];
    }
    
    std::vector<query> queries(q);

    for (int i = 0; i < q; i++) {
        std::cin >> queries[i].left >> queries[i].right;
        queries[i].index = i;
    }
    
    std::sort(queries.begin(), queries.end(), [](const query& a, const query& b) {
        return a.right < b.right;
    });
    
    std::vector<int> answers(q);
    segmentTree tree(n + 1);
    std::map<int, int> last_position;
    int query_idx = 0;
    
    for (int pos = 1; pos <= n; pos++) {
        int value = arr[pos];
        
        if (last_position.count(value)) {
            int prev_pos = last_position[value];
            tree.update(prev_pos, 0);
        }
        
        tree.update(pos, 1);
        last_position[value] = pos;
        
        while (query_idx < q && queries[query_idx].right == pos) {
            int left = queries[query_idx].left;
            int right = queries[query_idx].right;
            int original_index = queries[query_idx].index;
            
            answers[original_index] = tree.query(left, right);
            query_idx++;
        }
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << answers[i] << "\n";
    }
}
