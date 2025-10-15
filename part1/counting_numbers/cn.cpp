/*
Your task is to count the number of integers between a and b where no two adjacent digits are the same.

Input

The only input line has two integers a and b.

Output

Print one integer: the answer to the problem.

Constraints

0 <= a <= b <= 10^{18}

Example
Input:
123 321

Output:
171
*/

#include <iostream>
#include <string>
#include <vector>

// digit position, lastDigit, isTight, leadingZero
// 20 because of 1e18 constraint -> max number has less than 20 digits
// 10 because options are 0 to 9 in decimal
long long dp[20][10][2][2];

long long count_valid_numbers(unsigned int pos, unsigned int lastDigit, bool isTight, bool leadingZero,
    const std::vector<unsigned int>& upperBoundDigits)
{
    auto memoized = dp[pos][lastDigit][isTight][leadingZero];

    if (memoized >= 0) {
        return memoized;
    }

    // if pos is past the amount of digits to be generated for the number, the generated number
    // is complete and valid. return 1 representing the valid number. These will be summed up.
    if (pos == upperBoundDigits.size()) {
        return 1;
    }

    long long total = 0;
    unsigned int options = isTight ? upperBoundDigits[pos] + 1 : 10;

    // For each valid digit, call function again to generate the rest of the digits in the number.
    // Each valid generation will return a 1 that will be summed.
    for (unsigned int i = 0; i < options; i++) {
        if (!leadingZero && i == lastDigit) continue;
        bool nextIsLeadingZero = leadingZero && i == 0;
        bool isNextTight = isTight && i == upperBoundDigits[pos];
        total += count_valid_numbers(pos + 1, i, isNextTight, nextIsLeadingZero, upperBoundDigits);
    }

    dp[pos][lastDigit][isTight][leadingZero] = total;
    return total;
}

int main() {
    std::fill(&dp[0][0][0][0], &dp[0][0][0][0] + 20*10*2*2, -1);

    unsigned long long a;
    unsigned long long b;
    std::cin >> a;
    std::cin >> b;

    std::string upperBoundString = std::to_string(b);
    std::string lowerBoundString = std::to_string(a - 1);
    std::vector<unsigned int> upperBoundDigits(upperBoundString.size());
    std::vector<unsigned int> lowerBoundDigits(lowerBoundString.size());

    for (unsigned long long i = 0; i < upperBoundString.size(); i++) {
        upperBoundDigits[i] = upperBoundString[i] - '0';
    }

    for (unsigned long long i = 0; i < lowerBoundString.size(); i++) {
        lowerBoundDigits[i] = lowerBoundString[i] - '0';
    }

    long long validUpToB = count_valid_numbers(0, 0, true, true, upperBoundDigits);

    // re-initialize the DP table for the second call because the DP table doesn't
    // account for the used upper bound, which changes between these calls.
    std::fill(&dp[0][0][0][0], &dp[0][0][0][0] + 20*10*2*2, -1);
    long long validUpToA = count_valid_numbers(0, 0, true, true, lowerBoundDigits);
    std::cout << (validUpToB - validUpToA) << "\n";
}
