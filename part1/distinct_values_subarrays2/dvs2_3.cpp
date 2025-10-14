#include <iostream>
#include <unordered_map>
int main() {
    unsigned int n;
    unsigned int k;
    std::cin >> n;
    std::cin >> k;

    unsigned long int arr[n];

    for (unsigned int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::unordered_map<unsigned long int, unsigned long int> distincts;
    unsigned int left = 0;
    unsigned int right = 0;
    unsigned long int subarrays = 0;

    while (right < n) {
        unsigned long int rightVal = arr[right];

        // Add the right element first
        distincts[rightVal]++;
        right++;
        
        // Shrink from left if needed
        while (distincts.size() > k) {
            unsigned long int leftVal = arr[left];
            distincts[leftVal]--;
            if (distincts[leftVal] == 0) distincts.erase(leftVal);
            left++;
        }
        
        // Count subarrays ending at position right-1
        subarrays += (right - left);
    }

    std::cout << subarrays << "\n";
}
