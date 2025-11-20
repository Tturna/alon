/*
Consider a xor pyramid where each number is the xor of lower-left and lower-right numbers.
Here is an example pyramid:

            9
          15  6
         4  11 13
       11  15 4 9
     1   10  5 1  8
   7   6   12 9  8  0
 8   15  9   5 12  4  4
2  10  5  12  9  5  1  5

Given the bottom row of the pyramid, your task is to find the topmost number.

Input

The first line has an integer n: the size of the pyramid.
The next line has n integers a_1,a_2,...,a_n: the bottom row of the pyramid.

Output

Print one integer: the topmost number.

Constraints

1 <= n <= 2 * 10^5
1 <= a_i <= 10^9

Example
Input:
8
2 10 5 12 9 5 1 5

Output:
9
*/

// ^ is the xor operator meaning 6 ^ 2 = 15
// xor(0) = 0
// xor(n) = n ^ xor(n - 1)
// xor(3) = 3 ^ (2 ^ (1 ^ 0)) = 1 ^ 2 ^ 3 = 3 ^ 3 = 0
//
// xor(1) = 1
// xor(2) = 3
// xor(3) = 0
// xor(4) = 4
// xor(5) = 1
// xor(6) = 7
// xor(7) = 0
// xor(8) = 8
// xor(9) = 1
// xor(10)= 11
// xor(11)= 0
// xor(12)= 12
//
// xor(n) {
//   mod = n % 4
//   switch mod {
//     case 0: return n;
//     case 1: return 1;
//     case 2: return n + 1;
//     case 3: return 0;
//   }
// }

#include <iostream>
#include <vector>
int main() {
    int n;
    std::cin >> n;

    std::vector<long long> botrow(n);

    for (int i = 0; i < n; i++) {
        std::cin >> botrow[i];
    }
}
