#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    int t,n, i, j;
    scanf("%d", &t);
    getchar();
    while(t--) {
        scanf("%d", &n);
        getchar();
        string name[25], line;
        int vote[1005][25];
        for(i = 1; i <= n; i++)
            getline(cin, name[i]);
        int m = 0;
        while(getline(cin, line)) {
            if(line == "")  break;
            stringstream sin;
            sin << line;
            int idx = 0;
            while(sin >> vote[m][idx])
                idx++;
            m++;
        }
        int Idx[1005] = {}, fire[25] = {};
        while(1) {
            int p[25] = {}, tot = 0;
            for(i = 0; i < m; i++) {
                while(Idx[i] < n && fire[vote[i][Idx[i]]])
                    Idx[i]++;
                if(Idx[i] < n) {
                    p[vote[i][Idx[i]]]++;
                    tot++;
                }
            }
            int half = tot/2 + tot%2;
            int mx = 0, mi = 0xffff;
            for(i = 1; i <= n; i++) {
                if(!fire[i]) {
                    if(p[i] > mx)
                        mx = p[i];
                    if(p[i] < mi)
                        mi = p[i];
                }
            }
            if(mx == mi || mx >= half) {
                for(i = 1; i <= n; i++)
                    if(p[i] == mx)
                        cout << name[i] << endl;
                break;
            }
            for(i = 1; i <= n; i++)
                if(p[i] == mi)
                    fire[i] = 1;
        }
        if(t)
            puts("");
    }
    return 0;
}
