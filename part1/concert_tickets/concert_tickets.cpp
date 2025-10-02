/*
There are n concert tickets available, each with a certain price. Then, m customers arrive, one
after another. Each customer announces the maximum price they are willing to pay for a ticket,
and after this, they will get a ticket with the nearest possible price such that it does not
exceed the maximum price.

Input

The first input line contains integers n and m: the number of tickets and the number of customers.
The next line contains n integers h_1,h_2,...,h_n: the price of each ticket.
The last line contains m integers t_1,t_2,...,t_m: the maximum price for each customer in
the order they arrive.

Output

Print, for each customer, the price that they will pay for their ticket. After this,
the ticket cannot be purchased again. If a customer cannot get any ticket, print -1.

Constraints

1 <= n, m <= 2 * 10^5
1 <= h_i, t_i <= 10^9

Example
Input:
5 3
5 3 7 8 5
4 8 3

Output:
3
8
-1
*/

#include <iostream>
#include <set>
#include <vector>

int main() {
    unsigned long int tickets;
    unsigned long int customers;
    std::cin >> tickets;
    std::cin >> customers;

    std::multiset<unsigned long int> prices;
    std::vector<unsigned long int> offers;

    for (unsigned long int i = 0; i < tickets; i++) {
        unsigned long int price;
        std::cin >> price;
        prices.insert(price);
    }

    for (unsigned long int i = 0; i < customers; i++) {
        unsigned long int offer;
        std::cin >> offer;
        offers.push_back(offer);
    }

    for (unsigned long int i = 0; i < customers; i++) {
        if (prices.size() == 0) {
            std::cout << "-1\n";
            continue;
        }

        auto fittingPrice = prices.lower_bound(offers[i]);

        if (fittingPrice == prices.begin() && *fittingPrice > offers[i]) {
            std::cout << "-1\n";
            continue;
        }

        if (fittingPrice == prices.end() || *fittingPrice > offers[i]) {
            fittingPrice--;
        }

        std::cout << *fittingPrice << "\n";
        prices.erase(fittingPrice);
    }
}
