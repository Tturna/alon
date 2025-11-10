/*
Your task is to calculate n binomial coefficients modulo 10^9+7.
A binomial coefficient {a \choose b} can be calculated using the formula
(a!)/(b! * (a - b)!). We assume that a and b are integers and 0 <= b <= a.

Input

The first input line contains an integer n: the number of calculations.
After this, there are n lines, each of which contains two integers a and b.

Output

Print each binomial coefficient modulo 10^9+7.

Constraints

1 <= n <= 10^5
0 <= b <= a <= 10^6

Example
Input:
3
5 3
8 1
9 5

Output:
10
8
126
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

const int MOD = 1000000007;

long long fastModPow(long long base, long long exponent) {
    base %= MOD;
    long long result = 1;

    // a^13 = a^(8 + 4 + 1) = a^8 * a^4 * a^1;

    while (exponent > 0) {
        if (exponent & 1) {
            // this only runs when the right-most bit is 1.
            // The first time, this either sets the result to a^1 or a^2 if exp is odd.
            // Multiplies the previously made new component to result.
            result = (result * base) % MOD;
        }

        // The first time, this creates a^2. This creates all the components
        // like a^4 and a^8, which get multiplied into the result next round (if needed).
        base = (base * base) % MOD;
        exponent = exponent >> 1;

        // rundown for a^13:
        // ------------------
        // 1. exp is odd -> result = 1 * a = a^1. base = a * a = a^2. exp = 6
        // 2. exp not odd -> base = a^2 * a^2 = a^4. exp = 3
        // 3. exp is odd -> result = a^4 * a^1. base = a^4 * a^4 = a^8. exp = 1
        // 4. exp is odd -> result = a^8 * a^4 * a^1. base = a^8 * a^8 = a^16. exp = 0.
        // 5. return a^8 * a^4 * a^1 = a^13. 
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> inputs;
    int maxInput = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;

        inputs.push_back({a, b});
        maxInput = std::max(std::max(a, b), maxInput);
    }

    std::vector<long long> factorials(maxInput + 1, 0);
    factorials[0] = 1;

    for (int i = 1; i <= maxInput; i++) {
        factorials[i] = (factorials[i - 1] * i) % MOD;
    }

    for (auto [a, b] : inputs) {
        long long ab = factorials[a - b];
        long long denom = (factorials[b] * ab) % MOD;
        long long b_inv = fastModPow(denom, MOD - 2);
        long long result = (factorials[a] * b_inv) % MOD;
        std::cout << result << "\n";
    }
}
