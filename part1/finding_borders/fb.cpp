/*
A border of a string is a prefix that is also a suffix of the string but not the whole string.
For example, the borders of abcababcab are ab and abcab.
Your task is to find all border lengths of a given string.

Input

The only input line has a string of length n consisting of characters a–z.

Output

Print all border lengths of the string in increasing order.

Constraints

1 <= n <= 10^6

Example
Input:
abcababcab

Output:
2 5
*/

#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    std::string inputString;
    std::cin >> inputString;
    int n = inputString.length();

    std::vector<int> prefixFunction(n, 0);

    // prefic function algorithm from Knuth-Morris-Pratt algorithm
    for (int i = 1; i < n; i++) {
        int j = prefixFunction[i - 1];

        while (j > 0 && inputString[i] != inputString[j]) {
            j = prefixFunction[j - 1];
        }

        if (inputString[i] == inputString[j]) {
            j++;
        }

        prefixFunction[i] = j;
    }

    // std::cout << "[";
    // for (auto b : prefixFunction) {
    //     std::cout << b << ", ";
    // }
    // std::cout << "]\n";

    std::string result;
    std::multiset<int> borderLengths;
    int k = n;

    while (k > 0) {
        k -= 1;
        int borderLength = prefixFunction[k];

        if (borderLength > 0) {
            borderLengths.insert(borderLength);
        }

        k = borderLength;
    }

    for (auto bl : borderLengths) {
        std::cout << bl << " ";
    }

    std::cout << "\n";
}
