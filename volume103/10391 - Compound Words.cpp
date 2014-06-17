#include <stdio.h>
#include <iostream>
#include <set>
using namespace std;
int main() {
    string line, s1, s2;
    set<string> S;
    while(cin >> line)
        S.insert(line);
    for(set<string>::iterator i = S.begin(); i != S.end(); i++) {
        int len = (*i).length();
        for(int j = 0; j < len-1; j++) {
            s1 = (*i).substr(0, j+1);
            s2 = (*i).substr(j+1, len-j);
            if(S.find(s1) != S.end() && S.find(s2) != S.end()) {
                cout << (*i) << endl;
                break;
            }

        }
    }
    return 0;
}
