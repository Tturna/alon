// This is Booth's algorithm allegedly. If this passes then wtf. The course material
// clearly said the O(n log^2 n) method should be enough, but clearly it's not fast enough
// for the submission system >:(
//
// You're asking for AI submissions at this point...
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    s += s;
    
    int i = 0, j = 1, k;
    
    while (i < n && j < n) {
        k = 0;
        while (k < n && s[i + k] == s[j + k]) k++;
        
        if (k == n) break;
        
        if (s[i + k] > s[j + k]) {
            i += k + 1;
            if (i == j) i++;
        } else {
            j += k + 1;
            if (i == j) j++;
        }
    }
    
    std::cout << s.substr(i < j ? i : j, n) << "\n";
}
