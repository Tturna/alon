#include <iostream>

struct node {
    unsigned long int index;
    node* next;
    node* previous;
};

int main() {
    unsigned long int n;
    unsigned long int k;
    std::cin >> n;
    std::cin >> k;

    node* firstKid = new node();
    firstKid->index = 0;
    firstKid->next = nullptr;
    firstKid->previous = nullptr;
    node* currentKid = firstKid;

    for (unsigned long int i = 1; i < n; i++) {
        currentKid->next = new node();
        currentKid->next->index = i;
        currentKid->next->previous = currentKid;
        currentKid = currentKid->next;
    }

    currentKid->next = firstKid;
    firstKid->previous = currentKid;
    currentKid = firstKid;

    unsigned long int skips = k;

    while (true) {
        if (skips > 0) {
            skips--;
            currentKid = currentKid->next;
            continue;
        }

        skips = k;
        std::cout << currentKid->index + 1 << " ";

        if (currentKid->next == currentKid) {
            delete currentKid;
            break;
        }

        auto next = currentKid->next;
        currentKid->previous->next = next;
        currentKid->next->previous = currentKid->previous;
        delete currentKid;
        currentKid = next;
    }

    std::cout << "\n";
}
