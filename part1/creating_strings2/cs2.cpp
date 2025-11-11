/*
Given a string, your task is to calculate the number of different strings that can be
created using its characters.

Input

The only input line has a string of length n. Each character is between a–z.

Output

Print the number of different strings modulo 10^9+7.

Constraints

1 <= n <= 10^6

Example
Input:
aabac

Output:
20
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
    std::string input;
    std::cin >> input;
    int n = input.length();

    std::vector<long long> factorials(n + 1, 0);
    factorials[0] = 1;

    for (int i = 1; i <= n; i++) {
        factorials[i] = (factorials[i - 1] * i) % MOD;
    }

    // aabac
    // if 5 unique characters, possibilities = 5!
    // we have 3 a's. Ways to sort them = 3!
    // Because every possible arrangement can include these mixes of identical characters,
    // the number of unique arrangements = 5! / 3!
    // If there were dupes of another character, then it would be multiplied with 3!.
    // Generally: arrangements = characters! / (dupe_arrangements1! * dupe_arrangements2! * ...)

    std::unordered_map<char, int> charCounts;
    std::unordered_set<char> dupeCharacters;

    for (auto character : input) {
        charCounts[character]++;

        if (charCounts[character] > 1) {
            dupeCharacters.insert(character);
        }
    }

    long long allArrangements = factorials[n];
    long long dupes = 1;

    for (auto dupeCharacter : dupeCharacters) {
        dupes = (dupes * factorials[charCounts[dupeCharacter]]) % MOD;
    }

    long long dupes_inv = fastModPow(dupes, MOD - 2);
    long long arrangements = (allArrangements * dupes_inv) % MOD;
    std::cout << arrangements << "\n";
}
