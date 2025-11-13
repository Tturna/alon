/*
Given a string, your task is to process operations where you reverse a substring of the
string. What is the final string after all the operations?

Input

The first input line has two integers n and m: the length of the string and the number of
operations. The characters of the string are numbered 1,2,...,n. The next line has a
string of length n that consists of characters A–Z. Finally, there are m lines that
describe the operations. Each line has two integers a and b: you reverse a substring
from position a to position b.

Output

Print the final string after all the operations.

Constraints

1 <= n, m <= 2 * 10^5
1 <= a <= b <= n

Example
Input:
7 2
AYBABTU
3 4
4 7

Output:
AYAUTBB
*/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct node {
    node* left, *right;
    int weight, size;
    char value;
    bool reversed;

    node (char val) {
        left = right = NULL;
        weight = rand();
        reversed = false;
        size = 1;
        value = val;
    }
};

int size(node* treap) {
    if (treap == NULL) return 0;
    return treap->size;
}

void pushReversal(node* treap) {
    if (treap == NULL || !treap->reversed) return;

    std::swap(treap->left, treap->right);

    if (treap->left != NULL) {
        treap->left->reversed = !treap->left->reversed;
    }

    if (treap->right != NULL) {
        treap->right->reversed = !treap->right->reversed;
    }

    treap->reversed = false;
}

void split(node* treap, node* &left, node* &right, int k) {
    if (treap == NULL) {
        left = right = NULL;
    } else {
        pushReversal(treap);

        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k - size(treap->left) - 1);
            left = treap;
        } else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }

        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void merge(node* &treap, node* left, node* right) {
    pushReversal(left);
    pushReversal(right);

    if (left == NULL) treap = right;
    else if (right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        } else {
            merge(right->left, left, right->left);
            treap = right;
        }

        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void print(node* treap) {
    if (treap == NULL) return;

    pushReversal(treap);
    print(treap->left);
    std::cout << treap->value;
    print(treap->right);
}

void freeTreap(node* treap) {
    if (treap == NULL) return;

    if (treap->left != NULL) {
        freeTreap(treap->left);
    }

    if (treap->right != NULL) {
        freeTreap(treap->right);
    }

    delete treap;
}

int main() {
    int strLen, opsCount;
    std::cin >> strLen >> opsCount;
    std::string inputString;
    std::cin >> inputString;

    std::vector<std::pair<int, int>> ops(opsCount);

    for (int i = 0; i < opsCount; i++) {
        int a, b;
        std::cin >> a >> b;
        ops[i] = {a - 1, b - 1};
    }

    // luo treap
    node* treap = NULL;

    for (int i = 0; i < strLen; i++) {
        merge(treap, treap, new node(inputString[i]));
    }

    // print(treap);
    // std::cout << "\n";

    node *left, *substringPart, *right;

    for (int i = 0; i < opsCount; i++) {
        int from = ops[i].first;
        int to = ops[i].second;

        // std::cout << "OP = (" << from << " -> " << to << ")\n";
        split(treap, left, substringPart, from);
        split(substringPart, substringPart, right, to - from + 1);

        // std::cout << "split into left, sub, right:\n";
        // print(left);
        // std::cout << ", ";
        // print(substringPart);
        // std::cout << ", ";
        // print(right);
        // std::cout << "\n";

        substringPart->reversed = !substringPart->reversed;
        merge(treap, left, substringPart);
        merge(treap, treap, right);

        // std::cout << "merged into:\n";
        // print(treap);
        // std::cout << "\n";
    }

    // std::cout << "result:\n";
    print(treap);
    std::cout << "\n";

    // std::cout << "freeing treap...\n";
    freeTreap(treap);
}
