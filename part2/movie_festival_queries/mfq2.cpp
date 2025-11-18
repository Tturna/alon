/*
In a movie festival, n movies will be shown. You know the starting and ending time of each movie.
Your task is to process q queries of the form: if you arrive and leave the festival at specific
times, what is the maximum number of movies you can watch? You can watch two movies if the
first movie ends before or exactly when the second movie starts. You can start the first movie
exactly when you arrive and leave exactly when the last movie ends.

Input

The first input line has two integers n and q: the number of movies and queries.
After this, there are n lines describing the movies. Each line has two integers a and b:
the starting and ending time of a movie. Finally, there are q lines describing the queries.
Each line has two integers a and b: your arrival and leaving time.

Output

Print the maximum number of movies for each query.

Constraints

1 <= n,q <= 2 * 10^5
1 <= a < b <= 10^6

Example
Input:
4 3
2 5
6 10
4 7
9 10
5 9
2 10
7 10

Output:
0
2
1
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    int n, q;
    std::vector<std::pair<int, int>> times;
    std::cin >> n >> q;

    int maxStartTime = 0;

    for (int i = 0; i < n; i++) {
        int startTime;
        int endTime;
        std::cin >> startTime;
        std::cin >> endTime;
        times.push_back({endTime, startTime});
        maxStartTime = std::max(maxStartTime, startTime);
    }

    std::sort(times.begin(), times.end());;

    std::vector<std::pair<int, int>> watchableMovies;
    watchableMovies.push_back(times[0]);
    int previousIndex = 0;
    int watchableCount = 1;

    for (int i = 1; i < n; i++) {
        if (times[i].second < times[previousIndex].first) continue;
        watchableMovies.push_back(times[i]);
        watchableCount++;
        previousIndex = i;
    }

    // std::cout << "all movies:\n";
    // for (int i = 0; i < n; i++) {
    //     std::cout << times[i].second << " " << times[i].first << "\n";
    // }

    // std::cout << "watchables:\n";
    // for (int i = 0; i < watchableCount; i++) {
    //     std::cout << watchableMovies[i].second << " " << watchableMovies[i].first << "\n";
    // }

    std::string result;
    for (int i = 0; i < q; i++) {
        int arrivalTime, departureTime;
        std::cin >> arrivalTime >> departureTime;
        // std::cout << "arrived / departed: watchables\n";
        std::cout << arrivalTime << " / " << departureTime << ": ";

        int low = 0;
        int high = watchableCount - 1;

        // find first watchable movie given arrival time
        while (low < high) {
            int mid = (low + high) / 2;

            if (watchableMovies[mid].second > arrivalTime) {
                high = mid;
            }
            else {
                low = mid + 1;
            }
        }

        // std::cout << "found first\n";
        int first = high;
        low = first;
        high = watchableCount - 1;

        // find first unwatchable movie given departure time
        while (low < high) {
            int mid = (low + high) / 2;

            if (watchableMovies[mid].first > departureTime) {
                high = mid;
            }
            else {
                low = mid + 1;
            }
        }

        // std::cout << "found last\n";
        int last = high;
        std::cout << last - first << "\n";

        result += std::to_string(last - first) + "\n";
    }

    std::cout << result;
}
