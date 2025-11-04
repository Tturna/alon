/*
Your task is to deliver mail to the inhabitants of a city. For this reason, you
want to find a route whose starting and ending point are the post office, and that goes
through every street exactly once.

Input

The first input line has two integers n and m: the number of crossings and streets.
The crossings are numbered 1, 2,...,n, and the post office is located at crossing 1.
After that, there are m lines describing the streets. Each line has two integers a and b:
there is a street between crossings a and b. All streets are two-way streets.
Every street is between two different crossings, and there is at most one street between two crossings.

Output

Print all the crossings on the route in the order you will visit them. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".

Constraints

2 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n

Example
Input:
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5

Output:
1 2 6 3 2 4 5 3 1
*/

#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
    int crossingCount;
    int streetCount;

    std::cin >> crossingCount;
    std::cin >> streetCount;

    std::vector<std::unordered_multiset<int>> connections(crossingCount);
    std::vector<int> degrees(crossingCount, 0);

    for (int i = 0; i < streetCount; i++) {
        int a;
        int b;
        std::cin >> a >> b;
        connections[a - 1].insert(b - 1);
        connections[b - 1].insert(a - 1);
        degrees[a - 1]++;
        degrees[b - 1]++;
    }

    bool impossible = false;

    for (int i = 0; i < crossingCount; i++) {
        if (degrees[0] == 0 || degrees[i] % 2 != 0) {
            impossible = true;
            break;
        }
    }

    if (impossible) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    // there is an euler circuit so use Hierholzer's algo
    std::vector<int> stack;
    std::vector<int> circuit;
    int visitedStreetCount = 0;
    stack.push_back(0);

    while (stack.size() > 0) {
        auto top = stack.back();
        auto degree = degrees[top];

        if (degree == 0) {
            circuit.push_back(top);
            stack.pop_back();
        }
        else {
            int nextNode = *connections[top].begin();
            visitedStreetCount++;

            // remove edge from graph
            connections[top].erase(connections[top].find(nextNode));
            connections[nextNode].erase(connections[nextNode].find(top));
            degrees[top]--;
            degrees[nextNode]--;

            stack.push_back(nextNode);
        }
    }

    // graph was disconnected but had an euler circuit
    if (visitedStreetCount < streetCount) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto node : circuit) {
        std::cout << node + 1 << " ";
    }

    std::cout << "\n";
}
