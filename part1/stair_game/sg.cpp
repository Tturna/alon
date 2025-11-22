/*
There is a staircase consisting of n stairs, numbered 1,2,...,n. Initially, each
stair has some number of balls. There are two players who move alternately. On each move,
a player chooses a stair k where k - 1 and it has at least one ball. Then,
the player moves any number of balls from stair k to stair k-1. The player who moves last
wins the game. Your task is to find out who wins the game when both players play optimally.
Note that if there are no possible moves at all, the second player wins.

Input

The first input line has an integer t: the number of tests. After this, t test cases are described:
The first line contains an integer n: the number of stairs.
The next line has n integers p_1,p_2,...,p_n: the initial number of balls on each stair.

Output

For each test, print "first" if the first player wins the game and "second" if the
second player wins the game.

Constraints

1 <= t <= 2 * 10^5
1 <= n <= 2 * 10^5
0 <= p_i <= 10^9
the sum of all n is at most 2 * 10^5

Example
Input:
3
3
0 2 1
4
1 1 1 1
2
5 3

Output:
first
second
first
*/

#include <iostream>
#include <vector>

int main() {
    int testCases;
    std::cin >> testCases;
    
    while (testCases) {
        int stairCount;
        std::cin >> stairCount;
        
        std::vector<int> balls(stairCount + 1);

        for (int i = 1; i <= stairCount; i++) {
            std::cin >> balls[i];
        }
        
        // Moving balls from odd stairs to even stairs lets the opponent move them
        // down to odd stairs again, effectively neutralizing your move. You can't move down
        // from stair 1. Moving balls down from an even stair lets your opponent also
        // neutralize your move but only until you move the balls down to stair 1.
        // Therefore I think we can ignore odd stairs and only consider even stairs for the
        // nim game.
        int xorSum = 0;
        for (int i = 2; i <= stairCount; i += 2) {
            xorSum ^= balls[i];
        }
        
        if (xorSum != 0) {
            std::cout << "first\n";
        } else {
            std::cout << "second\n";
        }

        testCases--;
    }
}
