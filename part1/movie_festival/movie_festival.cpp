/*
In a movie festival n movies will be shown. You know the starting and ending time of each movie.
What is the maximum number of movies you can watch entirely?

Input

The first input line has an integer n: the number of movies.
After this, there are n lines that describe the movies. Each line has two integers a and b: the starting and ending times of a movie.

Output

Print one integer: the maximum number of movies.

Constraints

1 <= n <= 2 * 10^5
1 <= a < b <= 10^9

Example
Input:
3
3 5
4 9
5 8

Output:
2
*/

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

unsigned long int f(std::vector<std::pair<unsigned long int, unsigned long int>>* times, unsigned long int index,
    std::unordered_map<unsigned long int, unsigned long int>* watchableChains
) {
    unsigned long int maxWatchableFromHere = 1;

    for (unsigned long int i = index; i < times->size() - 1; i++) {
        auto current = (*times)[index];
        auto next = (*times)[i + 1];

        if (next.first < current.second) continue;

        unsigned long int watchableFromHere = 0;

        if (watchableChains->find(i + 1) != watchableChains->end()) {
            watchableFromHere = (*watchableChains)[i + 1];
        }
        else {
            watchableFromHere = f(times, i + 1, watchableChains) + 1;
        }

        if (watchableFromHere > maxWatchableFromHere) {
            maxWatchableFromHere = watchableFromHere;
        }
    }

    (*watchableChains)[index] = maxWatchableFromHere;

    return maxWatchableFromHere;
}

int main() {
    unsigned long int n;
    std::vector<std::pair<unsigned long int, unsigned long int>> times;
    std::cin >> n;

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int st;
        unsigned long int et;
        std::cin >> st;
        std::cin >> et;
        times.push_back({st, et});
    }

    std::sort(times.begin(), times.end());;

    std::unordered_map<unsigned long int, unsigned long int> watchableChains;
    unsigned long int maxWatchable = 1;

    for (unsigned long int i = 0; i < n; i++) {
        auto maxWatchableFromHere = f(&times, i, &watchableChains);

        if (maxWatchableFromHere > maxWatchable) {
            maxWatchable = maxWatchableFromHere;
        }
    }

    std::cout << maxWatchable << "\n";
}
