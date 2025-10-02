#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    unsigned long int n;
    std::vector<std::pair<unsigned long int, unsigned long int>> times;
    std::cin >> n;

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int st;
        unsigned long int et;
        std::cin >> st;
        std::cin >> et;
        times.push_back({et, st});
    }

    std::sort(times.begin(), times.end());;

    unsigned long int watchedMovies = 1;
    unsigned long int previousIndex = 0;

    for (unsigned long int i = 1; i < n; i++) {
        if (times[i].second < times[previousIndex].first) continue;

        previousIndex = i;
        watchedMovies++;
    }

    std::cout << watchedMovies << "\n";
}
