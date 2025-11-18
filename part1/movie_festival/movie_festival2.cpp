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
