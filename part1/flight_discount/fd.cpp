/*
Your task is to find a minimum-price flight route from Syrjälä to Metsälä.
You have one discount coupon, using which you can halve the price of any single
flight during the route. However, you can only use the coupon once. When you use the
discount coupon for a flight whose price is x, its price becomes floor(x/2)
(it is rounded down to an integer).

Input

The first input line has two integers n and m: the number of cities and flight connections.
The cities are numbered 1,2,...,n. City 1 is Syrjälä, and city n is Metsälä.
After this there are m lines describing the flights. Each line has three integers a, b, and c:
a flight begins at city a, ends at city b, and its price is c. Each flight is unidirectional.
You can assume that it is always possible to get from Syrjälä to Metsälä.

Output

Print one integer: the price of the cheapest route from Syrjälä to Metsälä.

Constraints

2 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n
1 <= c <= 10^9

Example
Input:
3 4
1 2 3
2 3 1
1 3 7
2 1 5

Output:
2
*/

#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct flight {
    int to;
    long long price;
};

struct node_data {
    long long distance;
    int node;
    int couponUsed;

    bool operator>(const node_data& other) const {
        return distance > other.distance;
    }

    bool operator<(const node_data& other) const {
        return distance < other.distance;
    }
};

int main() {
    int cityCount;
    int flightCount;

    std::cin >> cityCount;
    std::cin >> flightCount;

    std::vector<std::vector<flight>> flights(cityCount);

    for (int i = 0; i < flightCount; i++) {
        int a;
        int b;
        int p;
        std::cin >> a;
        std::cin >> b;
        std::cin >> p;
        flight f;
        f.to = b - 1;
        f.price = p;
        flights[a - 1].push_back(f);
    }

    std::priority_queue<node_data, std::vector<node_data>, std::greater<node_data>> heap;
    std::vector<std::vector<bool>> processed(cityCount, std::vector<bool>(2, false));

    // distance and whether coupon is used
    std::vector<std::vector<long long>> distances(cityCount, std::vector<long long> (2, std::numeric_limits<long long>::max()));

    heap.push({0, 0, false});
    distances[0][0] = 0;

    while (!heap.empty()) {
        auto top = heap.top();
        int node = top.node;
        long long distance = top.distance;
        int couponUsed = top.couponUsed;
        heap.pop();

        if (processed[node][couponUsed]) continue;

        processed[node][couponUsed] = true;

        for (auto flight : flights[node]) {
            auto currentDistance = distances[flight.to][couponUsed];
            auto newDistance = distance + flight.price;

            if (newDistance < currentDistance) {
                distances[flight.to][couponUsed] = newDistance;
                heap.push({newDistance, flight.to, couponUsed});
            }

            if (!couponUsed) {
                long long discountedDistance = distance + flight.price / 2;

                if (discountedDistance < distances[flight.to][true]) {
                    distances[flight.to][true] = discountedDistance;
                    heap.push({discountedDistance, flight.to, true});
                }
            }
        }
    }

    std::cout << distances[cityCount - 1][true] << "\n";
}
