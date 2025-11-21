/*
Your task is to count the number of sequences of length n where each element is an integer
between 1 ... k and each integer between 1 ... k appears at least once in the sequence.
For example, when n=6 and k=4, some valid sequences are [1,3,1,4,3,2] and [2,2,1,3,4,2].

Input

The only input line has two integers n and k.

Output

Print one integer: the number of sequences modulo 10^9+7.

Constraints

1 <= k <= n <= 10^6

Example
Input:
6 4

Output:
1560
*/

#include <algorithm>
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
    int n, k;
    std::cin >> n >> k;
    int maxInput = std::max(n, k);

    // ncr(n,k) = n!/(k!*(n-k)!)
    // ncr(n,k) = fact(n) / (fact(k) * fact(n - k))
    // ncr(n,k) = fact(n) * invfact(k) * invfact(n - k)

    std::vector<long long> factorial(maxInput + 1);
    std::vector<long long> invFactorial(maxInput + 1);
    factorial[1] = 1;

    for (int i = 2; i <= maxInput; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }

    invFactorial[maxInput] = fastModPow(factorial[maxInput], MOD - 2);

    for (int i = maxInput; i >= 1; i--) {
        invFactorial[i - 1] = (invFactorial[i] * i) % MOD;
    }

    long long result = 0;

    for (int i = 0; i < k; i++) {
        long long binom = ((factorial[k] * invFactorial[i] % MOD) * invFactorial[k - i]) % MOD;
        long long change = fastModPow(k - i, n);
        long long term = (binom * change) % MOD;

        if (i % 2 == 0) {
            result += term;

            if (result >= MOD) {
                result -= MOD;
            }
        } else {
            result -= term;

            if (result < 0) {
                result += MOD;
            }
        }
    }

    std::cout << result << "\n";
}
