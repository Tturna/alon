/*
You would like to write a list of positive integers 1,2,3,... using your computer.
However, you can press each key 0–9 at most n times during the process.
What is the last number you can write?

Input

The only input line contains the value of n.

Output

Print the last number you can write.

Constraints

1 <= n <= 10^{18}

Example
Input:
5

Output:
12

Explanation: You can write the numbers 1,2,...,12. This requires that you press key 1
five times, so you cannot write the number 13.
*/

#include <iostream>

long long digitCountInNum(int digit, long long num) {
    long long high = num;
    long long cur = 0;
    long long low = 0;
    long long pos = 1;
    long long digitCount = 0;

    while (pos <= num) {
        // std::cout << "pos: " << pos << "\n";
        high = num / pos;
        low = num % pos;
        cur = high % 10;
        high /= 10;

        // std::cout << "high / cur / low:\n" << high << " / " << cur << " / " << low << "\n";

        if (digit == 0) {
            if (high == 0) {
            } else if (cur == 0) {
                digitCount += (high - 1) * pos + (low + 1);
            } else {
                digitCount += high * pos;
            }
        }
        else if (cur > digit) {
            digitCount += (high + 1) * pos;
        }
        else if (cur == digit) {
            digitCount += (high * pos) + (low + 1);
        }
        else if (cur < digit) {
            digitCount += high * pos;
        }

        pos *= 10;
    }

    return digitCount;
}

bool isOverDigitLimit(long long num, long long limit) {
    for (int i = 0; i < 10; i++) {
        if (digitCountInNum(i, num) > limit) return true;
    }

    return false;
}

int main() {
    long long n;
    std::cin >> n;

    long long low = 0;
    long long high = 1000000000000000000;

    while (low < high) {
        long long mid = (low + high + 1) / 2;

        if (isOverDigitLimit(mid, n)) {
            high = mid - 1;
        }
        else {
            low = mid;
        }
    }

    std::cout << high << "\n";
}
