/*
You are given a string of length n. For every integer between 1 ... n you need to print
the number of distinct substrings of that length.

Input

The only input line has a string of length n that consists of characters a–z.

Output

For each integer between 1 ... n print the number of distinct substrings of that length.

Constraints

1 <= n <= 10^5

Example
Input:
abab

Output:
2 2 2 1
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string inputString;
    std::cin >> inputString;
    int n = inputString.length();

    // create suffix array

    // label, character index
    std::vector<std::pair<int, int>> singleLabels(n);
    // label pair left, right, and character index
    std::vector<std::tuple<int, int, int>> characterPairLabels(n);

    // initial single labels based on character order in the alphabet
    for (int i = 0; i < n; i++) {
        singleLabels[i] = {inputString[i] - 'a' + 1, i};
    }

    for (int k = 1; k < n; k *= 2) {
        // create label pairs
        for (int i = 0; i < n; i++) {
            int second = i + k >= n ? 0 : singleLabels[i + k].first;
            characterPairLabels[i] = {singleLabels[i].first, second, i};
        }

        std::sort(characterPairLabels.begin(), characterPairLabels.end());

        // assign new labels based on label pairs
        int newLabel = 1;
        auto firstLabelTuple = characterPairLabels[0];
        // set first new label so next ones can compare to previous in the loop
        singleLabels[std::get<2>(firstLabelTuple)] = {newLabel, std::get<2>(firstLabelTuple)};

        for (int i = 1; i < n; i++) {
            auto labelTuple = characterPairLabels[i];
            auto left = std::get<0>(labelTuple);
            auto right = std::get<1>(labelTuple);
            auto charIndex = std::get<2>(labelTuple);

            auto prevTuple = characterPairLabels[i - 1];
            auto prevLeft = std::get<0>(prevTuple);
            auto prevRight = std::get<1>(prevTuple);

            if (left != prevLeft || right != prevRight) {
                newLabel++;
            }

            singleLabels[charIndex] = {newLabel, charIndex};
        }
    }

    std::sort(singleLabels.begin(), singleLabels.end());
    std::vector<int> suffixArray(n);
    std::vector<int> rankArray(n);

    for (int i = 0; i < n; i++) {
        suffixArray[i] = singleLabels[i].second;
        rankArray[singleLabels[i].second] = i;
    }

    // create LCP using the Kasai algorithm
    std::vector<long long> lcp(n);
    long long currentCommonPrefixLength = 0;

    for (int i = 0; i < n; i++) {
        if (rankArray[i] == 0) {
            lcp[rankArray[i]] = 0;
            continue;
        }

        long long prevSuffixStart = suffixArray[rankArray[i] - 1];

        while (i + currentCommonPrefixLength < n &&
            prevSuffixStart + currentCommonPrefixLength < n &&
            inputString[i + currentCommonPrefixLength] ==
            inputString[prevSuffixStart + currentCommonPrefixLength])
        {
            currentCommonPrefixLength++;
        }

        lcp[rankArray[i]] = currentCommonPrefixLength;

        if (currentCommonPrefixLength > 0) {
            currentCommonPrefixLength--;
        }
    }

    // std::cout << "suffix array:\n";
    // for (int i = 0; i < n; i++) {
    //     std::cout << suffixArray[i] << " ";
    // }
    // std::cout << "\n";
    //
    // std::cout << "lcp:\n";
    // for (int i = 0; i < n; i++) {
    //     std::cout << lcp[i] << " ";
    // }
    // std::cout << "\n";

    long long uniqueSubstringCount = 0;
    std::vector<int> substringsOfLength(n + 1, 0);

    for (int i = 0; i < n; i++) {
        long long suffixLength = n - suffixArray[i];
        long long substrings = suffixLength - lcp[i];
        uniqueSubstringCount += substrings;

        // use substringsOfLength like a difference array. Add +1 to start of addition range
        // and -1 one step after the end of the range. A 1-pass sum afterwards creates
        // a prefix sum. Normally this would be added to the starting array, but our
        // start is nothing.
        substringsOfLength[lcp[i] + 1]++;

        if (suffixLength + 1 <= n) {
            substringsOfLength[suffixLength + 1]--;
        }

        // for (int j = lcp[i] + 1; j <= suffixLength; j++) {
        //     substringsOfLength[j]++;
        // }
    }

    // create prefix sum array from difference array, which is the final result.
    for (int i = 1; i <= n; i++) {
        substringsOfLength[i] += substringsOfLength[i - 1];
    }

    // std::cout << "total unique substrings:\n";
    // std::cout << uniqueSubstringCount << "\n";

    for (int i = 1; i <= n; i++) {
        std::cout << substringsOfLength[i] << " ";
    }
    std::cout << "\n";
}
