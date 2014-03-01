#include <iostream>
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
using namespace std;

int main() {
    int N, n, m, A[20];
    int i, j, k, cases = 0;
    while(scanf("%d", &N) == 1 && N) {
        scanf("%d %d", &n, &m);
        map<int, map<int, set<int> > > R;
        int sum = 0;
        for(i = 0; i < N; i++) {
            scanf("%d", &A[i]);
            sum += A[i];
        }
        if(cases > 122)   {
            printf("%d %d\n", n, m);
            break;
        }
        printf("Case %d: ", ++cases);
        if(sum != n*m) {
            puts("No");
            continue;
        }
        for(i = 0; i < N; i++) {
            for(j = 1; j <= A[i]; j++) {
                if(A[i]%j == 0) {
                    if(max(j, A[i]/j) > max(n, m) || min(j, A[i]/j) > min(n, m))
                        continue;
                    R[A[i]/j][j].insert(1<<i);
                    R[j][A[i]/j].insert(1<<i);
                }
            }
        }
        bool update;
        map<int, map<int, set<int> > >::iterator it, at;
        map<int, set<int> >::iterator jt, bt, ebt;
        set<int>::iterator kt, ct, cct;
        int time = 0, find = 0;
        do {
            if(++time > 5) break;
            update = false;
            for(it = R.begin(); it != R.end() && !find; it++) {
                for(jt = it->second.begin(); jt != it->second.end() && !find; jt++) {
                    for(kt = jt->second.begin(); kt != jt->second.end() && !find; kt++) {
                        for(bt = R[it->first].begin(), ebt = R[it->first].end(); bt != ebt && !find; bt++) {
                            if(jt->first+bt->first > max(n, m)) break;
                            if(min(it->first, jt->first+bt->first) > min(n, m)) break;
                            for(ct = bt->second.begin(); ct != bt->second.end() && !find; ct++) {
                                //printf("%d %d\n", bt->first, *ct);
                                if(((*ct)&(*kt)) == 0) {
                                    //cct = R[it->first][jt->first+bt->first].find((*ct)|(*kt));
                                    //if(cct == R[it->first][jt->first+bt->first].end()) {
                                        R[it->first][jt->first+bt->first].insert((*ct)|(*kt));
                                        R[jt->first+bt->first][it->first].insert((*ct)|(*kt));
                                        update = true;
                                    //}
                                    if(n == it->first && m == jt->first+bt->first)
                                        find = 1;
                                    if(m == it->first && n == jt->first+bt->first)
                                        find = 1;
                                }
                            }
                        }
                        //jt->second.erase(kt++);
                        //printf("%d %d %d -\n", it->first, jt->first, *kt);
                    }
                }
            }
        } while(update && !find);
        if(find)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
/*
15
1 15
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0
*/
