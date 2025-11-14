/*
Your task is to count the number of one bits in the binary representations of
integers between 1 and n.

Input

The only input line has an integer n.

Output

Print the number of one bits in the binary representations of integers between 1 and n.

Constraints

1 <= n <= 10^{15}

Example
Input:
7

Output:
12

Explanation: The binary representations of 1 ... 7 are 1, 10, 11, 100, 101, 110,
and 111, so there are a total of 12 one bits.
*/

#include <iostream>
int main() {
    long long n;
    std::cin >> n;

    // the bits have patterns. consider n = 11:
    //
    // bit pos k:   3  2  1  0
    //
    // 11 =         1  0  1  1
    // 10 =         1  0  1  0
    //  9 =         1  0  0  1
    //  8 =         1  0  0  0
    //  7 =         0  1  1  1
    //  6 =         0  1  1  0
    //  5 =         0  1  0  1
    //  4 =         0  1  0  0
    //  3 =         0  0  1  1
    //  2 =         0  0  1  0
    //  1 =         0  0  0  1
    //  0 =         0  0  0  0
    //
    // bits at pos k = 0 have a pattern of size 2 (01).
    // at k = 1 the pattern size is 4 (0011)
    // The pattern size is 2^{k+1}

    long long totalSetBits = 0;
    // add 1 to account for 0. The binary patterns start from 0.
    n++;

    // count set bits in each bit position. -1 to prevent going past the last bit and
    // another -1 to account for the sign bit.
    for (unsigned int k = 0; k < sizeof(long long) * 8 - 2; k++) {
        long long patternSize = 1LL << (k + 1);
        long long fullPatterns = n / patternSize;
        long long setBitsInFullPatterns = fullPatterns * patternSize / 2;
        // std::cout << "\nset bits in pos " << k << ": " << setBitsInFullPatterns << "\n";
        long long leftOverValues = n % patternSize;
        // std::cout << "leftOverValues: " << leftOverValues << "\n";
        totalSetBits += setBitsInFullPatterns;

        // only half the bits in a full pattern are set
        if (leftOverValues > patternSize / 2) {
            long long leftOverSetBits = leftOverValues - patternSize / 2;
            // std::cout << "leftover set bits: " << leftOverSetBits << "\n";
            totalSetBits += leftOverSetBits;
        }
    }

    std::cout << totalSetBits << "\n";
}
