#include <iostream>
#include <list>

int main() {
    unsigned long int n;
    unsigned long int k;
    std::cin >> n;
    std::cin >> k;

    std::list<unsigned long int> children;

    for (unsigned long int i = 0; i < n; i++) {
        children.push_back(i);
    }

    auto it = children.begin();

    while (!children.empty()) {
        unsigned long int steps = (k % children.size());
        
        for (unsigned long int j = 0; j < steps; j++) {
            ++it;
            if (it == children.end()) {
                it = children.begin();
            }
        }

        std::cout << *it + 1 << " ";
        
        auto next = it;
        ++next;
        if (next == children.end()) {
            next = children.begin();
        }
        
        children.erase(it);
        it = next;
    }

    std::cout << "\n";
    return 0;
}
