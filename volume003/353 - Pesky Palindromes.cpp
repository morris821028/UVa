#include <iostream>
#include <string.h>
#include <set>
using namespace std;
int main() {
    string s;
    while(cin >> s) {
        set<string> p;
        int i, len = s.length(), l, r;
        for(i = 0; i < len; i++) {
            l = i, r = i;
            while(l >= 0 && r < len && s[l] == s[r]) {
                p.insert(s.substr(l, r-l+1));
                l--, r++;
            }
            if(i != len-1 && s[i] == s[i+1]) {
                l = i, r = i+1;
                while(l >= 0 && r < len && s[l] == s[r]) {
                    p.insert(s.substr(l, r-l+1));
                    l--, r++;
                }
            }
        }
        cout << "The string '" << s << "' contains " << p.size() << " palindromes."<< endl;
    }
    return 0;
}
