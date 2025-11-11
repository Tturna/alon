/*
There are n children and m apples that will be distributed to them.
Your task is to count the number of ways this can be done.
For example, if n=3 and m=2, there are 6 ways: [0,0,2], [0,1,1], [0,2,0], [1,0,1], [1,1,0] and [2,0,0].

Input

The only input line has two integers n and m.

Output

Print the number of ways modulo 10^9+7.

Constraints

1 <= n,m <= 10^6

Example
Input:
3 2

Output:
6
*/

#include <iostream>
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
    int childCount, appleCount;
    std::cin >> childCount >> appleCount;

    // ncr(a, b) = (a!)/(b! * (a - b)!)
    // ncr(n+k-1,k)

    int maxInput = childCount + appleCount;
    std::vector<long long> factorials(maxInput + 1, 0);
    factorials[0] = 1;

    for (int i = 1; i <= maxInput; i++) {
        factorials[i] = (factorials[i - 1] * i) % MOD;
    }

    long long a = childCount + appleCount - 1;
    long long b = appleCount;
    long long ab = factorials[a - b];
    long long denom = (factorials[b] * ab) % MOD;
    long long b_inv = fastModPow(denom, MOD - 2);
    long long result = (factorials[a] * b_inv) % MOD;

    std::cout << result << "\n";
}
