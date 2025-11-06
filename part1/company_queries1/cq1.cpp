/*
A company has n employees, who form a tree hierarchy where each employee has a boss,
except for the general director. Your task is to process q queries of the form:
who is employee x's boss k levels higher up in the hierarchy?

Input

The first input line has two integers n and q: the number of employees and queries.
The employees are numbered 1,2,...,n, and employee 1 is the general director.
The next line has n-1 integers e_2,e_3,...,e_n: for each employee 2,3,...,n their boss.
Finally, there are q lines describing the queries. Each line has two integers x and k:
who is employee x's boss k levels higher up?

Output

Print the answer for each query. If such a boss does not exist, print -1.

Constraints

1 <= n,q <= 2 * 10^5
1 <= e_i <= i-1
1 <= x <= n
1 <= k <= n

Example
Input:
5 3
1 1 3 3
4 1
4 2
4 3

Output:
3
1
-1
*/

#include <iostream>
#include <string>
#include <vector>

int main() {
    int employeeCount;
    int queryCount;

    std::cin >> employeeCount >> queryCount;

    int maxExponent = 1;
    while (1 << maxExponent <= employeeCount) maxExponent++;
    std::vector<std::vector<int>> jumpTable(employeeCount, std::vector<int>(maxExponent, -1));

    for (int i = 1; i < employeeCount; i++) {
        int to;
        std::cin >> to;
        jumpTable[i][0] = to - 1;
    }

    for (int exponent = 1; exponent < maxExponent; exponent++) {
        for (int i = 1; i < employeeCount; i++) {
            int prev = jumpTable[i][exponent - 1];

            if (prev != -1) {
                jumpTable[i][exponent] = jumpTable[prev][exponent - 1];
            }
        }
    }

    std::string result;

    for (int i = 0; i < queryCount; i++) {
        int employee;
        int k;
        std::cin >> employee >> k;
        employee--;

        for (int j = 0; j < maxExponent; j++) {
            if (k & (1 << j)) {
                employee = jumpTable[employee][j];

                if (employee == -1) break;
            }
        }

        if (employee != -1) employee++;
        result += std::to_string(employee) + "\n";
    }

    std::cout << result;
}
