#include <iostream>
#include <list>

int main() {
    unsigned long int n, k;
    std::cin >> n >> k;
    
    std::list<unsigned long int> children;
    for (unsigned long int i = 1; i <= n; i++) {
        children.push_back(i);
    }
    
    auto it = children.begin();
    
    while (!children.empty()) {
        unsigned long int steps = k % children.size();
        
        for (unsigned long int i = 0; i < steps; i++) {
            ++it;
            if (it == children.end()) it = children.begin();
        }
        
        std::cout << *it;
        if (children.size() > 1) std::cout << " ";
        
        auto next = std::next(it);
        if (next == children.end()) next = children.begin();
        children.erase(it);
        it = next;
    }
    
    std::cout << "\n";
    return 0;
}
