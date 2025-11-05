#include <cstdlib>
#include <iostream>
#include <vector>

struct node {
    int componentId = 0;
    int cycleEntry = 0;
    int cyclePosition = -1; // >= 0 if in cycle, < 0 if before cycle
    int cycleSize = 0;
};

int main() {
    int planetCount, queryCount;
    std::cin >> planetCount >> queryCount;

    std::vector<int> teleporterDestination(planetCount);

    for (int i = 0; i < planetCount; ++i) {
        std::cin >> teleporterDestination[i];
        teleporterDestination[i]--;
    }

    std::vector<std::pair<int, int>> queries(queryCount);

    for (int i = 0; i < queryCount; ++i) {
        int from, to;
        std::cin >> from >> to;
        queries[i] = {from - 1, to - 1};
    }

    // visited, fully processed
    std::vector<std::pair<bool, bool>> visited(planetCount, {false, false});
    std::vector<node> nodes(planetCount);
    std::vector<int> stack;

    for (int i = 0; i < planetCount; ++i) {
        if (visited[i].first) continue;

        int cur = i;
        while (!visited[cur].first) {
            visited[cur].first = true;
            stack.push_back(cur);
            cur = teleporterDestination[cur];
        }

        if (!visited[cur].second) {
            // Found a cycle
            int cycleStart = cur;
            std::vector<int> cycleNodes;

            // find cycle nodes
            while (true) {
                int node = stack.back();
                stack.pop_back();
                cycleNodes.push_back(node);
                visited[node].second = true;
                if (node == cycleStart) break;
            }

            int cycleSize = cycleNodes.size();

            // set cycle node data
            for (int j = 0; j < cycleSize; ++j) {
                int node = cycleNodes[cycleSize - 1 - j];
                nodes[node].componentId = i;
                nodes[node].cycleEntry = node;
                nodes[node].cyclePosition = j;
                nodes[node].cycleSize = cycleSize;
            }

            // Handle path leading into the cycle
            int dist = -1;

            while (!stack.empty()) {
                int node = stack.back();
                stack.pop_back();
                visited[node].second = true;
                nodes[node].componentId = i;
                nodes[node].cycleEntry = cycleStart;
                nodes[node].cyclePosition = dist;
                nodes[node].cycleSize = cycleSize;
                dist--;
            }
        } else {
            // Already processed node
            int entry = cur;
            int dist = std::min(nodes[entry].cyclePosition, 0) - 1;

            // connect to existing segment
            while (!stack.empty()) {
                int node = stack.back();
                stack.pop_back();
                visited[node].second = true;
                nodes[node].componentId = nodes[entry].componentId;
                nodes[node].cycleEntry = nodes[entry].cycleEntry;
                nodes[node].cyclePosition = dist;
                nodes[node].cycleSize = nodes[entry].cycleSize;
                dist--;
            }
        }
    }

    // jump table to quickly see if destination is in front of start node
    int maxPower = 0;
    while ((1 << maxPower) <= planetCount) maxPower++;

    std::vector<std::vector<int>> jump(maxPower, std::vector<int>(planetCount));
    jump[0] = teleporterDestination;

    for (int k = 1; k < maxPower; ++k) {
        for (int i = 0; i < planetCount; ++i) {
            jump[k][i] = jump[k - 1][jump[k - 1][i]];
        }
    }

    auto teleportNTimes = [&](int start, int steps) {
        int planet = start;
        for (int k = 0; steps > 0; ++k) {
            if (steps & 1) planet = jump[k][planet];
            steps >>= 1;
        }
        return planet;
    };

    for (auto query : queries) {
        auto fromPlanet = query.first;
        auto toPlanet = query.second;
        // std::cout << "q: " << fromPlanet + 1 << ", " << toPlanet + 1 << "\n";
        const node &from = nodes[fromPlanet];
        const node &to = nodes[toPlanet];

        if (from.componentId != to.componentId) {
            std::cout << -1 << "\n";
            continue;
        }

        // both outside cycle
        if (from.cyclePosition < 0 && to.cyclePosition < 0) {
            // from planet is not behind to planet -> unreachable
            if (from.cyclePosition > to.cyclePosition) {
                // std::cout << "from in front of dest\n";
                // std::cout << "from pos: " << from.cyclePosition << ", to pos: " << to.cyclePosition << "\n";
                std::cout << -1 << "\n";
                continue;
            }

            int distance = std::abs(from.cyclePosition - to.cyclePosition);
            int landed = teleportNTimes(fromPlanet, distance);
            std::cout << (landed == toPlanet ? distance : -1) << "\n";
            continue;
        }

        // both in cycle
        if (from.cyclePosition >= 0 && to.cyclePosition >= 0) {
            int dist = to.cyclePosition - from.cyclePosition;
            if (dist < 0) dist += from.cycleSize;
            std::cout << dist << "\n";
            continue;
        }

        // start outside, destination in cycle
        if (from.cyclePosition < 0 && to.cyclePosition >= 0) {
            int distanceToCycle = abs(from.cyclePosition);
            int landed = teleportNTimes(fromPlanet, distanceToCycle);
            int entryPosition = nodes[landed].cyclePosition;

            int cycleDistance = to.cyclePosition - entryPosition;
            if (cycleDistance < 0) cycleDistance += nodes[landed].cycleSize;

            std::cout << distanceToCycle + cycleDistance << "\n";
            continue;
        }

        // start in cycle, destination outside cycle -> impossible
        std::cout << -1 << "\n";
    }
}
