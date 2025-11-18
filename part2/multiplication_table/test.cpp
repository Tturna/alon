#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int m = i * j;
            nums.push_back(m);

            if (m < 100) {
                std::cout << " ";

                if (m < 10) {
                    std::cout << " ";
                }
            }

            std::cout << i * j << " ";
        }
        std::cout << "\n";
    }

    std::sort(nums.begin(), nums.end());

    std::cout << "mid: " << nums[n * n / 2] << "\n";
}
