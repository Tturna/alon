/*
Your task is to divide the numbers 1,2,...,n into two sets of equal sum.

Input

The only input line contains an integer n.

Output

Print "YES", if the division is possible, and "NO" otherwise.
After this, if the division is possible, print an example of how to create the sets.
First, print the number of elements in the first set followed by the elements themselves in
a separate line, and then, print the second set in a similar way.

Constraints

1 <= n <= 10^6

Example 1
Input:
7

Output:
YES
4
1 2 4 7
3
3 5 6

Example 2
Input:
6

Output:
NO
*/

#include <iostream>
#include <vector>

int main() {
    unsigned long int n;
    std::cin >> n;
    std::vector<unsigned long int> left;
    std::vector<unsigned long int> right;

    if (n == 3) {
        std::cout << "YES\n";
        std::cout << "2\n";
        std::cout << "1 2\n";
        std::cout << "1\n";
        std::cout << "3\n";
        return 0;
    }

    if (n % 4 == 0) {
        // Sum from ends
        unsigned int referenceRemainder = 0;

        for (unsigned long int i = 1; i <= n; i++) {
            if (i % 2 == referenceRemainder) {
                left.push_back(i);
            }
            else {
                right.push_back(i);
            }

            if (i == n / 2) {
                referenceRemainder = 1;
            }
        }
    }
    else if ((n + 1) % 4 == 0) {
        // Add 1 and 2 into set 1, 3 into set 2, and then sum from ends
        left.push_back(1);
        left.push_back(2);
        right.push_back(3);

        unsigned int referenceRemainder = 0;

        for (unsigned long int i = 4; i <= n; i++) {
            if (i % 2 == referenceRemainder) {
                left.push_back(i);
            }
            else {
                right.push_back(i);
            }

            if (i == (n + 3) / 2) {
                referenceRemainder = 1;
            }
        }
    }
    else {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    std::cout << left.size() << "\n";

    for (unsigned int i = 0; i < left.size(); i++) {
        std::cout << left[i] << " ";
    }

    std::cout << "\n" << right.size() << "\n";

    for (unsigned int i = 0; i < right.size(); i++) {
        std::cout << right[i] << " ";
    }

    std::cout << "\n";
}
