/*
There is a large hotel, and n customers will arrive soon. Each customer wants to have
a single room. You know each customer's arrival and departure day. Two customers can stay in
the same room if the departure day of the first customer is earlier than the arrival day of
the second customer. What is the minimum number of rooms that are needed to accommodate all
customers? And how can the rooms be allocated?

Input

The first input line contains an integer n: the number of customers.
Then there are n lines, each of which describes one customer. Each line has two integers a and b:
the arrival and departure day.

Output

Print first an integer k: the minimum number of rooms required.
After that, print a line that contains the room number of each customer in the same order
as in the input. The rooms are numbered 1,2,...,k. You can print any valid solution.

Constraints

1 <= n <= 2 * 10^5
1 <= a <= b <= 10^9

Example
Input:
3
1 2
2 4
4 4

Output:
2
1 2 1
*/

#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main() {
    unsigned long int n;
    std::multiset<std::pair<unsigned long int, unsigned long int>> days;
    std::multiset<unsigned long int> roomReservations;
    std::vector<unsigned long int> usedRooms;
    std::cin >> n;

    for (unsigned long int i = 0; i < n; i++) {
        unsigned long int arrival;
        unsigned long int departure;
        std::cin >> arrival;
        std::cin >> departure;
        days.insert({departure, arrival});
    }

    for (auto c : days) {
        auto arr = c.second;
        auto dep = c.first;
        bool roomCleaned = false;

        for (unsigned long int i = 0; i < roomReservations.size(); i++) {
            auto begin = roomReservations.begin();
            if (*begin < arr) {
                roomReservations.erase(begin);
                roomReservations.insert(dep);
                usedRooms.push_back(i + 1);
                roomCleaned = true;
                break;
            }
        }

        if (!roomCleaned) {
            roomReservations.insert(dep);
            usedRooms.push_back(roomReservations.size());
        }
    }

    std::cout << usedRooms.size() << "\n";

    for (auto roomNum : usedRooms) {
        std::cout << roomNum << " ";
    }

    std::cout << "\n";
}
