#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
struct p {
    string name;
    int a, b;
};
p P[10];
int at, def;
bool cmp(p a, p b) {
    int i;
    for(i = 0; i < a.name.length() && i < b.name.length(); i++)
        if(a.name[i] > b.name[i])
            return 0;
        else if(a.name[i] < b.name[i])
            return 1;
    return a.name.length() < b.name.length();
}
int A[10], B[10];
int aA[10], aB[10];
void dfs(int idx, int a, int d, int ta, int td) {
    if(idx == 10) {
        if(ta > at || (ta == at && td > def)) {
            at = ta, def = td;
            int i;
            for(i = 0; i < 5; i++)
                aA[i] = A[i], aB[i] = B[i];
        }
        return;
    }
    if(a != 5) {
        A[a] = idx;
        dfs(idx+1, a+1, d, ta+P[idx].a, td);
    }
    if(d != 5) {
        B[d] = idx;
        dfs(idx+1, a, d+1, ta, td+P[idx].b);
    }
}
int main() {
    int t, cases = 0, i;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 10; i++)
            cin >> P[i].name >> P[i].a >> P[i].b;
        sort(P, P+10, cmp);
        at = 0, def = 0;
        dfs(0, 0, 0, 0, 0);
        printf("Case %d:\n", ++cases);
        printf("(");
        for(i = 0; i < 5; i++) {
            if(i)   printf(", ");
            cout << P[aA[i]].name;
        }
        printf(")\n");
        printf("(");
        for(i = 0; i < 5; i++) {
            if(i)   printf(", ");
            cout << P[aB[i]].name;
        }
        printf(")\n");
    }
    return 0;
}
