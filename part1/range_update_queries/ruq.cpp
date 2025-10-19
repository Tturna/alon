/*
Given an array of n integers, your task is to process q queries of the following types:

increase each value in range [a,b] by u
what is the value at position k?

Input

The first input line has two integers n and q: the number of values and queries.
The second line has n integers x_1,x_2,...,x_n: the array values.
Finally, there are q lines describing the queries. Each line has three integers: either "1 a b u" or "2 k".

Output

Print the result of each query of type 2.

Constraints

1 <= n,q <= 2 * 10^5
1 <= x_i, u <= 10^9
1 <= k <= n
1 <= a <= b <= n

Example
Input:
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4

Output:
5
6
*/

#include <iostream>
#include <vector>

int main() {
    long n;
    long q;
    std::cin >> n;
    std::cin >> q;

    std::vector<long> arr(n);

    for (long i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    for (long i = 0; i < q; i++) {
        int type;
        long first;
        std::cin >> type;
        std::cin >> first;

        if (type == 1) {
            long second;
            long third;
            std::cin >> second;
            std::cin >> third;

            for (long i = first - 1; i <= second - 1; i++) {
                arr[i] += third;
            }

            continue;
        }

        std::cout << arr[first - 1] << " ";
    }

    std::cout << "\n";
}
