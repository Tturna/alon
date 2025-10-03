#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main() {
    unsigned long int n;
    std::cin >> n;

    // customer departure time, room id.
    // Use this order to sort by departure time.
    std::set<std::pair<unsigned long int, unsigned long int>> usedRooms;
    std::vector<std::pair<std::pair<unsigned long int, unsigned long int>, unsigned long int>> customers;
    std::vector<unsigned long int> assignments(n);
    unsigned long int maxRooms = 0;

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int arrival;
        unsigned long int departure;
        std::cin >> arrival;
        std::cin >> departure;
        customers.push_back({{arrival, departure}, i});
    }

    std::sort(customers.begin(), customers.end());

    for (unsigned long int i = 0; i < n; i++) {
        auto customerId = customers[i].second;
        auto arrival = customers[i].first.first;
        auto departure = customers[i].first.second;

        // "Greedy" system that always picks the first room because it can assume it will be the
        // first available one. Then just check if it is available. If so, replace customer and
        // if not, place customer in a new room.
        auto begin = usedRooms.begin();

        if (usedRooms.size() == 0 || (*begin).first >= arrival) {
            auto roomId = usedRooms.size() + 1;
            usedRooms.insert({departure, roomId});
            assignments[customerId] = roomId;
            maxRooms = roomId; // happens to be the amount of rooms
            continue;
        }

        auto roomId = (*begin).second;
        usedRooms.erase(begin);
        usedRooms.insert({departure, roomId});
        assignments[customerId] = roomId;
    }

    std::cout << maxRooms << "\n";

    for (unsigned long int i = 0; i < assignments.size(); i++) {
        std::cout << assignments[i] << " ";
    }

    std::cout << "\n";
}
