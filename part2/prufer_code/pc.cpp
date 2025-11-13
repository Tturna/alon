/*
A Prüfer code of a tree of n nodes is a sequence of n-2 integers that uniquely specifies
the structure of the tree. The code is constructed as follows: As long as there are at
least three nodes left, find a leaf with the smallest label, add the label of its only
neighbor to the code, and remove the leaf from the tree. Given a Prüfer code of a tree,
your task is to construct the original tree.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered
1,2,...,n. The second line contains n-2 integers: the Prüfer code.

Output

Print n-1 lines describing the edges of the tree. Each line has to contain two integers
a and b: there is an edge between nodes a and b. You can print the edges in any order.

Constraints

3 <= n <= 2 * 10^5
1 <= a,b <= n

Example
Input:
5
2 2 4

Output:
1 2
2 3
2 4
4 5
*/

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> pruefer(n - 2);

    for (int i = 0; i < n - 2; i++) {
        std::cin >> pruefer[i];
    }

    // Every node appears in the pruefer code as many times as it has neighbors - 1.
    // So if code = [2, 2, 4], then 2 has a degree of 3 and 4 has a degree of 2. The
    // rest of the nodes have a degree of 1 (they're leaves).
    // The biggest node is never in the pruefer code.
    std::vector<int> degrees(n + 1, 1);

    for (auto val : pruefer) {
        degrees[val]++;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;

    for (int i = 1; i <= n; i++) {
        if (degrees[i] == 1) {
            leaves.push(i);
        }
    }

    // pruefer code generation starts by removing the smallest leaf and recording its neighbor.
    // Therefore the smallest leaf and pruefer[0] form the first edge.
    // The restored leaf can then be removed and the process repeated for all pruefer code values.
    // As edges are restored, node degrees are decremented to find pruefer code values that
    // are themselves removed by the pruefer code process.

    for (int i = 0; i < n - 2; i++) {
        int smallestLeaf = leaves.top();
        int pru = pruefer[i];

        std::cout << smallestLeaf << " " << pru << "\n";

        leaves.pop();
        degrees[pru]--;

        if (degrees[pru] == 1) {
            leaves.push(pru);
        }
    }

    // at this point the only two remaining nodes should be the biggest leaf and the
    // other that didn't get removed by the pruefer code generation.
    int a = leaves.top();
    leaves.pop();
    int b = leaves.top();
    std::cout << a << " " << b << "\n";
}
