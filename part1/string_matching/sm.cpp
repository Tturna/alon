/*
Given a string and a pattern, your task is to count the number of positions where
the pattern occurs in the string.

Input

The first input line has a string of length n, and the second input line has a pattern
of length m. Both of them consist of characters a–z.

Output

Print one integer: the number of occurrences.

Constraints

1 <= n,m <= 10^6

Example
Input:
saippuakauppias
pp

Output:
2
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string inputString, inputPattern;
    std::cin >> inputString >> inputPattern;

    std::string ab = inputPattern + "#" + inputString;
    int bLength = inputPattern.length();
    int abLength = ab.length();
    std::vector<int> zArray(abLength, 0);
    int rightEdge = 0;
    int leftEdge = 0;

    int occurrences = 0;
    for (int i = 1; i < abLength; i++) {
        if (rightEdge >= i) {
            // zArray[i] = zArray[bLength - (rightEdge - i)];
            zArray[i] = std::min(zArray[i - leftEdge], rightEdge - i);

            // if precomputed match length goes out of matched window, fall through
            // and check for more matches
            if (zArray[i] != rightEdge - i) continue;
        }

        for (int j = 0; j <= abLength; j++) {
            if (j == abLength || ab[j] != ab[i + j]) break;
            leftEdge = i;
            rightEdge = i + j;
            zArray[i]++;
        }

        if (i > bLength && zArray[i] >= bLength) {
            occurrences++;
        }
    }

    std::cout << occurrences << "\n";
}
