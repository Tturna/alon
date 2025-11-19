/*
There will be a chess tournament of n players. Each player has announced the number of
games they want to play. Each pair of players can play at most one game. Your task is
to determine which games will be played so that everybody will be happy.

Input

The first input line has an integer n: the number of players. The players are numbered
1,2,...,n. The next line has n integers x_1,x_2,...,x_n: for each player, the number
of games they want to play.

Output

First print an integer k: the number of games. Then, print k lines describing the games.
You can print any valid solution. If there are no solutions, print "IMPOSSIBLE".

Constraints

1 <= n <= 10^5
\sum_{i=1}^{n} x_i <= 2 * 10^5

Example
Input:
5
1 3 2 0 2

Output:
4
1 2
2 3
2 5
3 5
*/

#include <functional>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::multiset<std::pair<int, int>, std::greater<std::pair<int, int>>> desiredGames;
    int desiredGamesSum = 0;

    for (int i = 0; i < n; i++) {
        int d;
        std::cin >> d;

        // If someone wants to play more games than there are available opponents,
        // they can't play all games.
        if (d >= n) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }

        desiredGamesSum += d;
        desiredGames.insert({d, i + 1});
    }

    // If the total amount of games people want to play is odd, there will be someone
    // who can't play their last game.
    if (desiredGamesSum % 2 == 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    std::vector<std::pair<int, int>> playedGames;

    while (!desiredGames.empty()) {
        auto topIt = desiredGames.begin();
        auto top = *topIt;
        desiredGames.erase(topIt);

        // If the player with the most desired games wants to play more games than there
        // are available opponents left, declare impossible
        if (top.first > (int)desiredGames.size()) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }

        std::vector<std::pair<int, int>> topOpponents;

        for (int i = 0; i < top.first; i++) {
            auto topOpponentIt = desiredGames.begin();
            topOpponents.push_back(*topOpponentIt);
            desiredGames.erase(topOpponentIt);
        }

        for (auto opp : topOpponents) {
            playedGames.push_back({top.second, opp.second});
            opp.first--;

            if (opp.first > 0) {
                desiredGames.insert(opp);
            }
        }
    }

    std::cout << playedGames.size() << "\n";
    
    for (auto game : playedGames) {
        std::cout << game.first << " " << game.second << "\n";
    }
}
