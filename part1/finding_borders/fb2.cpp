#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    std::string inputString;
    std::cin >> inputString;
    int n = inputString.length();

    std::vector<int> zArray(n, 0);

    int leftEdge = 0;
    int rightEdge = 0;

    for (int i = 1; i < n; i++) {
        if (i <= rightEdge) {
            zArray[i] = std::min(zArray[i - leftEdge], rightEdge - i + 1);
        }

        while (i + zArray[i] < n && inputString[zArray[i]] == inputString[i + zArray[i]]) {
            zArray[i]++;
        }

        if (i + zArray[i] - 1 > rightEdge) {
            leftEdge = i;
            rightEdge = i + zArray[i] - 1;
        }
    }

    std::multiset<int> borders;

    for (int i = 0; i < n; i++) {
        int z = zArray[i];

        if (i + z == n) {
            // z = how far a substring starting from here matches the start of the
            // given string. If z > 0, there's some match. If z reaches the end of
            // the string, it matches both the start and the end, i.e. is a border.
            borders.insert(z);
        }
    }

    for (auto b : borders) {
        std::cout << b << " ";
    }

    std::cout << "\n";
}
