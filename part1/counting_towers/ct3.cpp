// #include <bits/stdc++.h>
// using namespace std;
// const long long MOD = 1e9 + 7;
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     int t;
//     cin >> t;
//     vector<int> queries(t);
//     int maxN = 0;
//     for (int &n : queries) {
//         cin >> n;
//         maxN = max(maxN, n);
//     }
//
//     vector<long long> dp0(maxN + 1), dp1(maxN + 1);
//     dp0[1] = dp1[1] = 1;
//
//     for (int i = 2; i <= maxN; i++) {
//         dp0[i] = (2 * dp0[i - 1] + dp1[i - 1]) % MOD;
//         dp1[i] = (dp0[i - 1] + 4 * dp1[i - 1]) % MOD;
//     }
//
//     for (int n : queries) {
//         cout << (dp0[n] + dp1[n]) % MOD << "\n";
//     }
// }

#include <iostream>
#include <vector>

int main() {
    const long long MOD = 1e9 + 7;
    int t;
    std::cin >> t;
    std::vector<int> testHeights;
    int maxHeight = 0;

    for (int i = 0; i < t; i++) {
        int h;
        std::cin >> h;
        testHeights.push_back(h);
        maxHeight = std::max(maxHeight, h);
    }

    std::vector<long long> dp0(maxHeight + 1), dp1(maxHeight + 1);
    dp0[1] = dp1[1] = 1;

    for (int i = 2; i <= maxHeight; i++) {
        dp0[i] = (2 * dp0[i - 1] + dp1[i - 1]) % MOD;
        dp1[i] = (dp0[i - 1] + 4 * dp1[i - 1]) % MOD;
    }

    for (int n : testHeights) {
        std::cout << (dp0[n] + dp1[n]) % MOD << "\n";
    }
}
