#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
using namespace __gnu_pbds;

typedef tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

int main() {
    unsigned long int n;
    unsigned long long k;
    std::cin >> n;
    std::cin >> k;

    indexed_set s;
    for (unsigned long int i = 1; i <= n; ++i) s.insert(i);

    long long idx = 0;

    while (!s.empty()) {
        idx = (idx + k) % s.size();
        auto it = s.find_by_order(idx);
        std::cout << *it << " ";
        s.erase(it);
    }

    std::cout << "\n";
}
