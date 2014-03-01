#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;

int main() {
    int t, n, m, i, j, k;
    int sub[120][30], subt[120];
    cin >> t;
    string line;
    while(t--) {
        cin >> n >> m;
        getline(cin, line);
        for(i = 0; i < m; i++) {
            getline(cin, line);
            stringstream sin;
            sin << line;
            subt[i] = 0;
            while(sin >> sub[i][subt[i]])
                sub[i][subt[i]]--, subt[i]++;
        }
        int flag = 0;
        for(i = (1<<n)-1; i >= 0; i--) {
            for(j = 0; j < m; j++) {
                int cnt = 0;
                for(k = 0; k < subt[j]; k++)
                    cnt += (i>>sub[j][k])&1;
                if(cnt == 0 || cnt == subt[j])
                    break;
            }
            if(j == m) {
                flag = 1;
                break;
            }
        }
        if(flag)    putchar('Y');
        else        putchar('N');
    }
    return 0;
}
/*
2
5 3
1 2 3
2 3 4
1 3 5

7 7
1 2
1 3
4 2
4 3
2 3
1 4
5 6 7
*/
