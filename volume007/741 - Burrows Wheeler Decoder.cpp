#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int p, i, j, k, first = 0;
    string msg;
    while(getline(cin, msg)) {
        if(msg == "END")    break;
        cin >> p;
        if(first)   cout << endl;
        first = 1;
        cin.ignore(100, '\n');
        int n = msg.length();
        string buf[n], res[n];
        for(i = 0; i < n; i++)
            buf[i] = msg[i], res[i] = buf[i];
        for(i = 0; i < n-1; i++) {
            sort(buf, buf+n);
            for(j = 0; j < n; j++)
                res[j] = res[j] + buf[j][i];
            for(j = 0; j < n; j++)
                buf[j] = res[j];
        }
        sort(buf, buf+n);
        cout << buf[p-1] << endl;
    }
    return 0;
}
