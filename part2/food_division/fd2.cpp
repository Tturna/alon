#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<long long> foodCounts(n);
    std::vector<long long> foodWants(n);

    for (int i = 0; i < n; i++) {
        std::cin >> foodCounts[i];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> foodWants[i];
    }
    
    std::vector<long long> diff(n);

    for (int i = 0; i < n; i++) {
        diff[i] = foodCounts[i] - foodWants[i];
    }
    
    // Compute all prefix sums
    std::vector<long long> prefix(n);
    prefix[0] = diff[0];

    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + diff[i];
    }
    
    // Collect all possible offsets (cutting after each position)
    std::vector<long long> offsets;
    offsets.push_back(0);

    for (int i = 0; i < n; i++) {
        offsets.push_back(prefix[i]);
    }
    
    std::sort(offsets.begin(), offsets.end());
    long long median = offsets[offsets.size() / 2];
    
    long long answer = 0;

    for (int i = 0; i < n; i++) {
        answer += std::abs(prefix[i] - median);
    }
    
    std::cout << answer << "\n";
}
