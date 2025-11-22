/*
There are n children around a round table. For each child, you know the amount of food
they currently have and the amount of food they want. The total amount of food in the
table is correct. At each step, a child can give one unit of food to his or her neighbour.
What is the minimum number of steps needed?

Input

The first input line contains an integer n: the number of children.
The next line has n integers a_1,a_2,...,a_n: the current amount of food for each child.
The last line has n integers b_1,b_2,...,b_n: the required amount of food for each child.

Output

Print one integer: the minimum number of steps.

Constraints

1 <= n <= 2 * 10^5
0 <= a_i, b_i <= 10^6

Example
Input:
3
3 5 0
2 4 2

Output:
2

Explanation: Child 1 gives one unit of food to child 3, and child 2 gives one unit of food to child 3.
*/

#include <climits>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<long long> foodCounts(n);
    std::vector<long long> foodWants(n);

    for (int i = 0; i < n; i++) {
        std::cin >> foodCounts[i];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> foodWants[i];
    }
    
    std::vector<long long> diff(n);

    for (int i = 0; i < n; i++) {
        diff[i] = foodCounts[i] - foodWants[i];
    }
    
    long long answer = LLONG_MAX;
    
    // Try each possible starting position
    for (int start = 0; start < n; start++) {
        long long prefix_sum = 0;
        long long total_steps = 0;
        
        for (int i = 0; i < n - 1; i++) {
            prefix_sum += diff[(start + i) % n];
            total_steps += std::abs(prefix_sum);
        }
        
        answer = std::min(answer, total_steps);
    }
    
    std::cout << answer << "\n";
}
