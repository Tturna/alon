#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string inputString, inputPattern;
    std::cin >> inputString >> inputPattern;

    std::string ab = inputPattern + "#" + inputString;
    int bLength = inputPattern.length();
    int abLength = ab.length();
    std::vector<int> zArray(abLength, 0);
    int leftEdge = 0;
    int rightEdge = 0;

    int occurrences = 0;
    for (int i = 1; i < abLength; i++) {
        if (i <= rightEdge) {
            // Copy the value from the corresponding position
            int k = i - leftEdge;
            zArray[i] = std::min(zArray[k], rightEdge - i + 1);
        }

        // Try to extend the match
        while (i + zArray[i] < abLength && ab[zArray[i]] == ab[i + zArray[i]]) {
            zArray[i]++;
        }

        // Update the window if we extended past the current right edge
        if (i + zArray[i] - 1 > rightEdge) {
            leftEdge = i;
            rightEdge = i + zArray[i] - 1;
        }

        // Check if we found a match (and it's in the text part, not pattern part)
        if (i > bLength && zArray[i] >= bLength) {
            occurrences++;
        }
    }

    std::cout << occurrences << "\n";
}
