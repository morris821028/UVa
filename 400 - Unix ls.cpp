#include <iostream>
#include <cstdio>
#include <iomanip>
#include <set>
using namespace std;

int main() {
    int n;
    while(cin >> n) {
        string s, d[n];
        set<string> in;
        int width = 0;
        for(int i = 0; i < n; i++) {
            cin >> s;
            in.insert(s);
            if(s.length() > width)
                width = s.length();
        }
        puts("------------------------------------------------------------");
        width += 2;
        if(width >= 60) width = 60;
        int idx = 0, m = 60/width;
        for(set<string>::iterator i = in.begin(); i != in.end(); i++) {
            d[idx++] = *i;
        }
        int l = n/m + (n%m != 0);
        for(int i = 0; i < l; i++) {
            for(int j = 0; i+j < n; j += l) {
                cout << left << setw(width) << d[i+j];
            }
            cout << endl;
        }
    }
    return 0;
}
