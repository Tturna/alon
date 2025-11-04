#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const long long INF = 1e18;
const int MOD = 1e9 + 7;

struct flight {
    int to;
    long long cost;
};

int main() {
    int cityCount, flightCount;
    std::cin >> cityCount >> flightCount;
    std::vector<std::vector<flight>> graph(cityCount);

    for (int i = 0; i < flightCount; i++) {
        int a;
        int b;
        long long c;
        std::cin >> a >> b >> c;
        graph[a - 1].push_back({b - 1, c});
    }

    std::vector<long long> distances(cityCount, INF);
    std::vector<long long> ways(cityCount, 0);
    std::vector<int> minFlights(cityCount, INT_MAX);
    std::vector<int> maxFlights(cityCount, 0);

    // distance-node pairs
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
    distances[0] = 0;
    ways[0] = 1;
    minFlights[0] = 0;
    maxFlights[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto pair = pq.top();
        auto distance = pair.first;
        auto node = pair.second;
        pq.pop();

        if (distance > distances[node]) continue;

        for (auto flight : graph[node]) {
            long long newDistance = distance + flight.cost;

            if (newDistance < distances[flight.to]) {
                distances[flight.to] = newDistance;
                ways[flight.to] = ways[node];
                minFlights[flight.to] = minFlights[node] + 1;
                maxFlights[flight.to] = maxFlights[node] + 1;
                pq.push({newDistance, flight.to});
            } else if (newDistance == distances[flight.to]) {
                ways[flight.to] = (ways[flight.to] + ways[node]) % MOD;
                minFlights[flight.to] = std::min(minFlights[flight.to], minFlights[node] + 1);
                maxFlights[flight.to] = std::max(maxFlights[flight.to], maxFlights[node] + 1);
            }
        }
    }

    std::cout << distances[cityCount - 1] << " " << ways[cityCount - 1] << " " << minFlights[cityCount - 1] << " " << maxFlights[cityCount - 1] << "\n";
}
