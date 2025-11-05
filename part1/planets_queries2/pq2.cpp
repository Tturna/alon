/*
You are playing a game consisting of n planets. Each planet has a teleporter to
another planet (or the planet itself). You have to process q queries of the form:
You are now on planet a and want to reach planet b. What is the minimum number of teleportations?

Input

The first input line contains two integers n and q: the number of planets and queries.
The planets are numbered 1,2,...,n. The second line contains n integers t_1,t_2,...,t_n:
for each planet, the destination of the teleporter. Finally, there are q lines describing the
queries. Each line has two integers a and b: you are now on planet a and want to reach planet b.

Output

For each query, print the minimum number of teleportations. If it is not possible to reach the
destination, print -1.

Constraints

1 <= n, q <= 2 * 10^5
1 <= a,b <= n

Example
Input:
5 3
2 3 2 3 2
1 2
1 3
1 4

Output:
1
2
-1
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

struct node {
    int componentId = 0;
    int cycleEntryNode = 0;
    int cyclePosition = 0; // >= 0 when in cycle, negative indicates distance from cycle
    int cycleSize = 0; // how many nodes in the cycle
};

int main() {
    int planetCount;
    int queryCount;

    std::cin >> planetCount;
    std::cin >> queryCount;

    std::vector<int> tp(planetCount);
    std::vector<std::pair<int, int>> queries(queryCount);

    for (int i = 0; i < planetCount; i++) {
        int tpDestination;
        std::cin >> tpDestination;
        tp[i] = tpDestination - 1;
    }

    for (int i = 0; i < queryCount; i++) {
        int from;
        int to;
        std::cin >> from >> to;
        queries[i] = {from - 1, to - 1};
    }

    // iterate each unvisited node and add them to a stack.
    // when encountering visited node that's in the stack, cycle found.
    // back track and set cycle position for each node in the cycle.
    // back track and set distance to cycle for each path node.

    // (is_visited, is_fully_processed)
    // fully processed means the node has been visited before in a previous loop
    // and leads to a processed cycle.
    std::vector<std::pair<bool, bool>> visited(planetCount);
    std::vector<node> nodes(planetCount);
    std::vector<int> stack;

    for (int i = 0; i < planetCount; i++) {
        if (visited[i].first) continue;

        int top = i;

        while (!visited[top].first) {
            stack.push_back(top);
            visited[top].first = true;
            top = tp[top];
        }

        if (visited[top].second) {
            // reached fully processed node
            int dist = std::min(nodes[top].cyclePosition, 0) - 1;
            while (stack.size() > 0) {
                int cur = stack.back();
                stack.pop_back();
                nodes[cur].cyclePosition = dist;
                nodes[cur].componentId = nodes[top].componentId;
                nodes[cur].cycleEntryNode = nodes[top].cycleEntryNode;
                visited[cur].second = true;
                dist--;
            }
        }
        else {
            // found cycle
            int cycleStartNode = top;
            int cycleSize = 0;
            std::vector<int> cycleNodes;

            while (true) {
                top = stack.back();
                stack.pop_back();
                cycleNodes.push_back(top);
                visited[top].second = true;
                cycleSize++;

                if (top == cycleStartNode) break;
            }

            for (int j = 0; j < cycleSize; j++) {
                int cycleNode = cycleNodes[cycleSize - 1 - j];
                nodes[cycleNode].cycleSize = cycleSize;
                nodes[cycleNode].cyclePosition = j;
                nodes[cycleNode].componentId = i;
                nodes[cycleNode].cycleEntryNode = cycleNode;
            }

            int dist = -1;
            while (stack.size() > 0) {
                top = stack.back();
                stack.pop_back();
                nodes[top].cyclePosition = dist;
                nodes[top].cycleEntryNode = cycleStartNode;
                nodes[top].componentId = i;
                visited[top].second = true;
                dist--;
            }
        }
    }

    for (int i = 0; i < queryCount; i++) {
        // std::cout << "(" << i << ") processing query...(" << queries[i].first + 1 << ", " << queries[i].second + 1 << ")\n";
        node from = nodes[queries[i].first];
        node to = nodes[queries[i].second];

        if (from.componentId != to.componentId) {
            // std::cout << "dif comp\n";
            std::cout << "-1\n";
            continue;
        }

        // start is in a cycle but destination is not -> unreachable
        if (from.cyclePosition >= 0 && to.cyclePosition < 0) {
            std::cout << "-1\n";
            continue;
        }

        // if neither are in a cycle
        if (from.cyclePosition < 0 && to.cyclePosition < 0) {
            // std::cout << "neither in cy\n";
            int cycleDistanceDiff = std::abs(from.cyclePosition - to.cyclePosition);
            int landed = queries[i].first;

            for (int l = 0; l < cycleDistanceDiff; l++) {
                landed = tp[landed];
            }

            // if destination is not in front of start, it's not reachable
            if (landed != queries[i].second) {
                std::cout << "-1\n";
            }
            else {
                std::cout << cycleDistanceDiff << "\n";
            }

            continue;
        }

        // both in cycle
        if (from.cyclePosition >= 0 && to.cyclePosition >= 0) {
            if (from.cyclePosition <= to.cyclePosition) {
                std::cout << to.cyclePosition - from.cyclePosition << "\n";
            }
            else {
                std::cout << from.cycleSize - from.cyclePosition + to.cyclePosition << "\n";
            }

            continue;
        }

        // start outside cycle, destination in cycle
        if (from.cyclePosition < 0 && to.cyclePosition >= 0) {
            node fromEntry = nodes[from.cycleEntryNode];
            if (fromEntry.cyclePosition <= to.cyclePosition) {
                std::cout << std::abs(from.cyclePosition) + to.cyclePosition - fromEntry.cyclePosition << "\n";
            }
            else {
                std::cout << std::abs(from.cyclePosition) + to.cycleSize - fromEntry.cyclePosition << "\n";
            }
        }
    }
}
