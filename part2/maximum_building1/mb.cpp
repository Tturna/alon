/*
You are given a map of a forest where some squares are empty and some squares have trees.
What is the maximum area of a rectangular building that can be placed in the forest so
that no trees must be cut down?

Input

The first input line contains integers n and m: the size of the forest.
After this, the forest is described. Each square is empty (.) or has trees (*).

Output

Print the maximum area of a rectangular building.

Constraints

1 <= n,m <= 1000

Example
Input:
4 7
...*.*.
.*.....
.......
......*

Output:
12
*/

#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> emptyHeights(n, std::vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char tile;
            std::cin >> tile;

            if (tile == '.') {
                // tile is empty. Record the amount of empty tiles above this and including itself.
                int prevHeight = i > 0 ? emptyHeights[i - 1][j] : 0;
                emptyHeights[i][j] = prevHeight + 1;
            }
            else {
                // tile is a tree. Empty tiles on and above this are 0
                emptyHeights[i][j] = 0;
            }
        }
    }

    int maxRectArea = 0;

    for (int i = 0; i < n; i++) {
        std::vector<int> stack;

        for (int j = 0; j <= m; j++) {
            int currHeight = (j == m ? -1 : emptyHeights[i][j]);

            // While the current height is smaller than the height at stack top:
            while (!stack.empty() && currHeight < emptyHeights[i][stack.back()]) {
                int poppedIndex = stack.back();
                stack.pop_back();

                int height = emptyHeights[i][poppedIndex];

                int leftBoundary = stack.empty() ? -1 : stack.back();
                int rightBoundary = j;

                int width = rightBoundary - leftBoundary - 1;
                int area = height * width;

                if (area > maxRectArea)
                    maxRectArea = area;
            }

            stack.push_back(j);
        }
    }

    std::cout << maxRectArea << "\n";
}
