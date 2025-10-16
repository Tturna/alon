/*
A factory has n machines which can be used to make products. Your goal is to make a
total of t products.

For each machine, you know the number of seconds it needs to make a single product.
The machines can work simultaneously, and you can freely decide their schedule.
What is the shortest time needed to make t products?

Input

The first input line has two integers n and t: the number of machines and products.
The next line has n integers k_1,k_2,...,k_n: the time needed to make a product using each machine.

Output

Print one integer: the minimum time needed to make t products.

Constraints

1 <= n <= 2 * 10^5
1 <= t <= 10^9
1 <= k_i <= 10^9

Example
Input:
3 7
3 2 5

Output:
8

Explanation: Machine 1 makes two products, machine 2 makes four
products and machine 3 makes one product.
*/

#include <algorithm>
#include <iostream>

int main() {
    long long machineCount;
    long long productsRequired;
    std::cin >> machineCount;
    std::cin >> productsRequired;

    long long machineProductionTimes[machineCount];
    long long fastestProductionSpeed = 1e9;

    for (long long i = 0; i < machineCount; i++) {
        std::cin >> machineProductionTimes[i];
        fastestProductionSpeed = std::min(fastestProductionSpeed, machineProductionTimes[i]);
    }

    const long long MAX_TIME = fastestProductionSpeed * productsRequired;

    long long min = 0;
    long long max = MAX_TIME;

    while (min < max) {
        long long totalProduced = 0;
        long long midTime = (min + max) / 2;

        for (long long i = 0; i < machineCount; i++) {
            // max time given for work / machine production time = num of products
            // that can be made in the given time. ints floor automatically.
            totalProduced += (midTime / machineProductionTimes[i]);

            if (totalProduced >= productsRequired) break;
        }

        if (totalProduced < productsRequired) {
            // try again with more time
            min = midTime + 1;
        }
        else {
            // if excess products were made, try again with less time.
            max = midTime;
        }
    }

    std::cout << min << "\n";
}
