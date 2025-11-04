/*
You are going to travel from Syrjälä to Lehmälä by plane. You would like to find answers to
the following questions:

what is the minimum price of such a route?
how many minimum-price routes are there? (modulo 10^9+7)
what is the minimum number of flights in a minimum-price route?
what is the maximum number of flights in a minimum-price route?

Input

The first input line contains two integers n and m: the number of cities and the number of
flights. The cities are numbered 1,2,...,n. City 1 is Syrjälä, and city n is Lehmälä.
After this, there are m lines describing the flights. Each line has three integers a, b,
and c: there is a flight from city a to city b with price c. All flights are one-way flights.
You may assume that there is a route from Syrjälä to Lehmälä.

Output

Print four integers according to the problem statement.

Constraints

1 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n
1 <= c <= 10^9

Example
Input:
4 5
1 4 5
1 2 4
2 4 5
1 3 2
3 4 3

Output:
5 2 1 2
*/

#include <iostream>
#include <vector>

struct flight {
    int to;
    long long price;

    flight(int nodeTo, long long price) {
        this->to = nodeTo;
        this->price = price;
    }
};

struct path {
    std::vector<int> pathNodes;
    long long totalCost;

    path() {
        totalCost = 0;
    }
};

void dfsAllPaths(int node, long long cost, int target, std::vector<std::vector<flight>>& graph,
    std::vector<bool>& visited, std::vector<path>& paths, path& path, long long& minPrice,
    long long& minPriceRoutes, int& minPriceMinFlights, int& minPriceMaxFlights) {
    path.pathNodes.push_back(node);
    path.totalCost += cost;

    if (node == target) {
        paths.push_back(path);

        if (path.totalCost < minPrice) {
            minPrice = path.totalCost;
            minPriceRoutes = 1;
            minPriceMinFlights = path.pathNodes.size() - 1;
            minPriceMaxFlights = path.pathNodes.size() - 1;
        }
        else if (path.totalCost == minPrice) {
            minPriceRoutes = (minPriceRoutes + 1) % 1000000007;
            int flights = path.pathNodes.size() - 1;

            if (flights < minPriceMinFlights) {
                minPriceMinFlights = flights;
            }
            else if (flights > minPriceMaxFlights) {
                minPriceMaxFlights = flights;
            }
        }

        path.pathNodes.pop_back();
        path.totalCost -= cost;
        return;
    }

    for (auto flight : graph[node]) {
        if (visited[flight.to]) continue;
        visited[flight.to] = true;
        dfsAllPaths(flight.to, flight.price, target, graph, visited, paths, path, minPrice,
            minPriceRoutes, minPriceMinFlights, minPriceMaxFlights);
        visited[flight.to] = false;
    }

    path.pathNodes.pop_back();
    path.totalCost -= cost;
}

int main() {
    int cityCount;
    int flightCount;

    std::cin >> cityCount;
    std::cin >> flightCount;

    std::vector<std::vector<flight>> adjacencyList(cityCount);

    for (int i = 0; i < flightCount; i++) {
        int a;
        int b;
        long long price;

        std::cin >> a;
        std::cin >> b;
        std::cin >> price;
        flight f = flight(b - 1, price);
        adjacencyList[a - 1].push_back(f);
    }

    std::vector<bool> visited(cityCount);
    std::vector<path> paths;
    path path;
    long long minPrice;
    long long minPriceRoutes;
    int minPriceMinFlights;
    int minPriceMaxFlights;
    dfsAllPaths(0, 0, cityCount - 1, adjacencyList, visited, paths, path, minPrice,
        minPriceRoutes, minPriceMinFlights, minPriceMaxFlights);

    // for (unsigned int i = 0; i < paths.size(); i++) {
    //     auto path = paths[i];
    //     std::cout << "Path " << i + 1 << " (" << path.totalCost << "): ";
    //
    //     for (auto node : path.pathNodes) {
    //         std::cout << node + 1 << " ";
    //     }
    //
    //     std::cout << "\n";
    // }

    std::cout << minPrice << " " << minPriceRoutes << " " << minPriceMinFlights << " " << minPriceMaxFlights << "\n";
}
