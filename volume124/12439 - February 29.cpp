#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char month[12][20] = {"January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December"};
int count(char str[], int d, int y, bool b) {
    if(y%4 == 0 && y%100 != 0 || y%400 == 0) {
        int i, m;
        for(i = 0; i < 12; i++) {
            if(!strcmp(str, month[i])) {
                m = i+1;
                break;
            }
        }
        if(m > 2) {
            y++;
        } else if(m == 2 && d == 29) {
            if(b == true)
                y++;
            else
                y--;
        } else {
            y--;
        }
    }
    return y/4 - y/100 + y/400;
}
int main() {
    int t, d, y, Case = 0;
    int cnt1, cnt2;
    char m[50];
    scanf("%d", &t);
    while(t--) {
        scanf("%s %d, %d", m, &d, &y);
        cnt1 = count(m, d, y, false);
        scanf("%s %d, %d", m, &d, &y);
        cnt2 = count(m, d, y, true);
        printf("Case %d: %d\n", ++Case, abs(cnt2 - cnt1));
    }
    return 0;
}
