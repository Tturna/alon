/*
You are given a string. You can remove any number of characters from it, but you cannot
change the order of the remaining characters. How many different strings can you generate?

Input

The first input line contains a string of size n. Each character is one of a–z.

Output

Print one integer: the number of strings modulo 10^9+7.

Constraints

1 <= n <= 5 * 10^5

Example
Input:
aybabtu

Output:
103
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const int MOD = 1000000007;

int main() {
    std::string inputString;
    std::cin >> inputString;
    int n = inputString.size();

    // total number of subsequences = 2^n (-1 if not counting empty string)

    // dp[i] = subsequences with i'th element as an option
    // dp[i] = 2 * dp[i - 1] (this overcounts because duplicate characters)
    // subtract dp[last[inputString[i]] - 1] to account for duplicates.
    // "last" gives the index of the last occurrence of the given character.

    std::vector<long long> dp(n + 1);
    dp[0] = 1; // can only be empty
    std::unordered_map<char, int> last;

    for (int i = 1; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) % MOD;
        auto c = inputString[i - 1];

        if (last.find(c) != last.end()) {
            dp[i] -= dp[last[c] - 1];
            dp[i] = (dp[i] + MOD) % MOD;
        }

        last[c] = i;
    }

    // -1 to ignore empty string as an option
    std::cout << (dp[n] - 1 + MOD) % MOD  << "\n";
}
