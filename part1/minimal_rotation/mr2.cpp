#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string inputString;
    std::cin >> inputString;
    int n = inputString.length();
    std::string doubleString = inputString + inputString;

    std::vector<int> rank(2 * n);
    std::vector<int> temp(2 * n);
    std::vector<int> pos(2 * n);

    // Initial ranks based on characters
    for (int i = 0; i < 2 * n; i++) {
        rank[i] = doubleString[i] - 'a';
        pos[i] = i;
    }

    for (int k = 1; k < n; k *= 2) {
        // Sort by (rank[i], rank[i+k])
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < 2 * n) ? rank[i + k] : -1;
            int rj = (j + k < 2 * n) ? rank[j + k] : -1;
            return ri < rj;
        };
        
        std::sort(pos.begin(), pos.end(), cmp);

        // Assign new ranks
        temp[pos[0]] = 0;
        for (int i = 1; i < 2 * n; i++) {
            temp[pos[i]] = temp[pos[i - 1]];
            if (cmp(pos[i - 1], pos[i])) {
                temp[pos[i]]++;
            }
        }
        rank = temp;
    }

    // Find minimum rotation (starting position < n)
    for (int i = 0; i < 2 * n; i++) {
        if (pos[i] < n) {
            std::cout << doubleString.substr(pos[i], n) << "\n";
            break;
        }
    }
}
