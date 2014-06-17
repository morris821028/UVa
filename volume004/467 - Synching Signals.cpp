#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    string line;
    int cases = 0;
    while(getline(cin, line)) {
        int v[7200] = {}, x;
        int i, j, k, cnt = 0;
        stringstream sin(line);
        int mx = 0xfffffff, time = 0xfffffff;
        while(sin >> x) {
            mx = min(mx, x);
            int base = -x;
            cnt++;
            while(base <= 3600) {
                base += x; // red
                for(i = base+1, j = 0; j < x-5; i++, j++)
                    v[i]++;
                base += x;
            }
        }
        for(i = mx; i <= 3601; i++) {
            if(v[i] == cnt) {
                time = i;
                break;
            }
        }
        time--;
        printf("Set %d ", ++cases);
        if(time <= 3600) {
            printf("synchs again at %d minute(s) and %d second(s) after all turning green.\n", time/60, time%60);
        } else {
            puts("is unable to synch after one hour.");
        }
    }
    return 0;
}
