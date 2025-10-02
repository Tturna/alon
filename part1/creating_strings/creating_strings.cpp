/*
Given a string, your task is to generate all different strings that can be created using its
characters.

Input

The only input line has a string of length n. Each character is between a–z.

Output

First print an integer k: the number of strings. Then print k lines: the strings in
alphabetical order.

Constraints

1 <= n <= 8

Example
Input:
aabac

Output:
20
aaabc
aaacb
aabac
aabca
aacab
aacba
abaac
abaca
abcaa
acaab
acaba
acbaa
baaac
baaca
bacaa
bcaaa
caaab
caaba
cabaa
cbaaa
*/

#include <iostream>
#include <string>
#include <set>
void f(std::string rem, std::string tot, std::set<std::string>* strs) {
    if (rem.length() == 0) {
        strs->insert(tot);
        return;
    }

    for (unsigned int i = 0; i < rem.length(); i++) {
        std::string new_rem = rem;
        new_rem.erase(i, 1);
        f(new_rem, tot + rem[i], strs);
    }
}

int main() {
    std::string in;
    std::cin >> in;
    std::set<std::string> strs;
    f(in, "", &strs);

    std::cout << strs.size() << "\n";

    for (std::string str : strs) {
        std::cout << str << "\n";
    }
}
