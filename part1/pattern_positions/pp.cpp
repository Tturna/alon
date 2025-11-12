/*
Given a string and patterns, find for each pattern the first position (1-indexed) where
it appears in the string.

Input

The first input line has a string of length n.
The next input line has an integer k: the number of patterns. Finally, there are k lines
that describe the patterns. The string and the patterns consist of characters a–z.

Output

Print the first position for each pattern (or -1 if it does not appear at all).

Constraints

1 <= n <= 10^5
1 <= k <= 5 * 10^5
the total length of the patterns is at most 5 * 10^5

Example
Input:
aybabtu
3
bab
abc
a

Output:
3
-1
1
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string inputString;
    int tests;
    std::cin >> inputString >> tests;

    int n = inputString.length();

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

    int treeSize = 1;
    while (treeSize < n) treeSize *= 2;
    std::vector<int> tree(2 * treeSize, 0);

    // insert leaf nodes into tree
    for (int i = 0; i < treeSize; i++) {
        int val = i < n ? singleLabels[i].second : 0;

        if (i < n) {
            suffixArray[i] = val;
        }

        tree[treeSize + i] = val;
    }

    // build internal nodes
    for (int i = treeSize - 1; i > 0; i--) {
        tree[i] = std::min(tree[2 * i], tree[2 * i + 1]);
    }

    // std::cout << "tree:\n";
    // for (auto v : tree) {
    //     std::cout << v << " ";
    // }
    // std::cout << "\n";

    auto lowerComparator = [&inputString](int start, const std::string &val) {
        return inputString.compare(start, val.size(), val) < 0;
    };

    auto upperComparator = [&inputString](const std::string &val, int start) {
        return inputString.compare(start, val.size(), val) > 0;
    };

    std::string result;
    for (int i = 0; i < tests; i++) {
        std::string pattern;
        std::cin >> pattern;
        auto lowerIt = std::lower_bound(suffixArray.begin(), suffixArray.end(), pattern, lowerComparator);
        auto upperIt = std::upper_bound(suffixArray.begin(), suffixArray.end(), pattern, upperComparator) - 1;
        int lowerIdx = lowerIt - suffixArray.begin();
        int upperIdx = upperIt - suffixArray.begin();

        if (upperIdx < 0) {
            result += std::to_string(upperIdx) + "\n";
            continue;
        }

        // std::cout << "lower idx: " << lowerIdx << "\n";
        // std::cout << "up idx: " << upperIdx << "\n";
        // std::cout << "lower: " << *lowerIt << "\n";
        // std::cout << "upper: " << *upperIt << "\n";

        // Verify the pattern actually matches at this position
        if (*lowerIt + (int)pattern.size() > n || inputString.compare(*lowerIt, pattern.size(), pattern) != 0) {
            result += "-1\n";
            continue;
        }

        // etsi välin a...b pienin alkio
        auto a = lowerIdx;
        auto b = upperIdx;
        a += treeSize; b += treeSize;
        int x = tree[a];

        while (a <= b) {
            if (a%2 == 1) x = std::min(x, tree[a++]);
            if (b%2 == 0) x = std::min(x, tree[b--]);
            a /= 2; b /= 2;
        }

        // std::cout << "lowest: " << x << "\n";

        // std::cout << "lower: " << lowerIdx << "\n";
        // std::cout << "upper: " << upperIdx << "\n";
        // result += std::to_string(upperIdx - lowerIdx + 1) + "\n";
        result += std::to_string(x + 1) + "\n";
    }

    std::cout << result;
}
