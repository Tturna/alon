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

    for (int i = 0; i < n; i++) {
        int startTime;
        int endTime;
        std::cin >> startTime;
        std::cin >> endTime;
        times.push_back({endTime, startTime});
    }

    std::sort(times.begin(), times.end());

    std::vector<int> nextMovies(n);

    for (int i = 0; i < n; i++) {
        // find first watchable movie after i'th movie.
        int low = std::min(i + 1, n - 1);
        int high = n - 1;
        
        while (low < high) {
            int mid = (low + high) / 2;

            if (times[mid].second < times[i].first) {
                low = mid + 1;
            }
            else {
                high = mid;
            }
        }

        if (times[high].second < times[i].first) {
            // no watchable movies left
            // std::cout << "next movie from " << i << " = -1" << "\n";
            nextMovies[i] = -1;
            continue;
        }

        // std::cout << "next movie from " << i << " = " << high << "\n";
        nextMovies[i] = high;
    }

    int ne = nextMovies[49];
    std::cout << "movie 49: " << times[49].second << " " << times[49].first << "\n";
    std::cout << "next after 49: " << ne << "\n";
    std::cout << times[ne].second << " " << times[ne].first << "\n";
    return 0;

    int maxK = 1;
    while (1 << maxK < n) maxK++;
    std::vector<std::vector<int>> dp(n, std::vector<int>(maxK + 1, -1));
    // std::cout << "maxK: " << maxK << "\n";

    for (int i = 0; i < n; i++) {
        dp[i][0] = nextMovies[i];
        // std::cout << "dp[" << i << "][0] = " << dp[i][0] << "\n";
    }

    for (int k = 1; k <= maxK; k++) {
        for (int i = 0; i < n; i++) {
            if (dp[i][k - 1] != -1) {
                dp[i][k] = dp[dp[i][k - 1]][k - 1];
            }

            // std::cout << "dp[" << i << "][" << k << "] = " << dp[i][k] << "\n";
        }
    }

    std::string result;
    for (int i = 0; i < q; i++) {
        int arrivalTime, departureTime;
        std::cin >> arrivalTime >> departureTime;
        std::cout << "arrival / departure\n";
        std::cout << arrivalTime << " / " << departureTime << "\n";

        // find first watchable movie given arrival time.
        int low = 0;
        int high = n - 1;
        
        while (low < high) {
            int mid = (low + high) / 2;

            if (times[mid].second < arrivalTime) {
                low = mid + 1;
            }
            else {
                high = mid;
            }
        }

        std::cout << "first watchable:\n";

        if (times[high].second < arrivalTime || times[high].first > departureTime) {
            // no watchable movies left
            result += "0\n";
            std::cout << "none\n";
            continue;
        }

        std::cout << high << "\n";

        int movie = high;
        int k = maxK;
        int watchable = 1;

        while (k >= 0) {
            if (dp[movie][k] != -1 && times[dp[movie][k]].first <= departureTime) {
                std::cout << "jumping 2^" << k << " movies\n";
                movie = dp[movie][k];
                watchable += (1 << k);
            }

            std::cout << "decrementing k from " << k << " to " << k - 1 << "\n";
            k--;
        }

        std::cout << "watchable: " << watchable << "\n";
        result += std::to_string(watchable) + "\n";
    }

    std::cout << result;
}
