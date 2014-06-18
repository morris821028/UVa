#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int old = 0, young = 2147483647;
        string oa, ya, name;
        int dd, mm, yy;
        while(n--) {
            cin >> name >> dd >> mm >> yy;
            dd = dd+mm*100+yy*10000;
            if(dd > old)    old = dd, oa = name;
            if(dd < young)  young = dd, ya = name;
        }
        cout << oa << endl;
        cout << ya << endl;
    }
    return 0;
}
