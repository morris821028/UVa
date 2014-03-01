#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;

int main() {
    int t;
    string line;
    scanf("%d", &t);
    getchar();
    while(t--) {
        getchar();
        int idx[5000], n = 1, i = 1;
        string x[5000];
        getline(cin, line);
        stringstream sin;
        sin << line;
        while(sin >> idx[n])
            n++;
        getline(cin, line);
        sin.clear();
        sin << line;
        while(sin >> x[idx[i]])
            i++;
        for(i = 1; i < n; i++)
            cout << x[i] << endl;
        if(t)
            puts("");
    }
    return 0;
}
