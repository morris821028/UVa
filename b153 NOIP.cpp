#include <stdio.h>
#include <stdlib.h>
int n;
char A[50], B[50], C[50];
char mapped[127], used[127] = {}, flag = 0;
char usednum[127] = {};
char MOD[127], DIV[127], V[127];
void dfs(int idx, int carry) {
    if(flag)    return;
    if(idx == -1) {
        if(carry == 0) {
            flag = 1;
            int i;
            for(i = 0; i < n; i++)
                printf("%d ", mapped['A'+i]);
            puts("");
        }
        return;
    }
    int a, b, c, i, j, ra = 0, rb = 0, rc = 0, ca = carry;
    for(i = idx; i >= 0; i--) {
        if(used[A[i]] && used[B[i]]) {
            if(used[C[i]]) {
                a = mapped[A[i]], b = mapped[B[i]], c = mapped[C[i]];
                if(MOD[a+b] != c && MOD[a+b+1] != c)
                    return;
            } else {
                a = mapped[A[i]], b = mapped[B[i]];
                if(usednum[MOD[a+b]] && usednum[MOD[a+b+1]])
                    return;
            }
            ca = (a+b+ca)/n;
        } else if(used[A[i]] && used[C[i]]) {
            a = mapped[A[i]], c = mapped[C[i]];
            if(usednum[MOD[c-a+n]] && usednum[MOD[c-a-1+n]])
                return;
            ca = 0;
        } else if(used[B[i]] && used[C[i]]) {
            b = mapped[B[i]], c = mapped[C[i]];
            if(usednum[MOD[c-b+n]] && usednum[MOD[c-b-1+n]])
                return;
            ca = 0;
        } else  ca = 0;
    }
    if(ca)  return;
    if(used[A[0]] && used[B[0]]) {
        if(mapped[A[0]]+mapped[B[0]] >= n)  return;
    }
    if(used[A[idx]] && used[B[idx]]) {
        if(used[C[idx]]) {
            if(MOD[carry+mapped[A[idx]]+mapped[B[idx]]] != mapped[C[idx]])
                return;
        } else {
            mapped[C[idx]] = MOD[carry+mapped[A[idx]]+mapped[B[idx]]];
            if(usednum[mapped[C[idx]]]) return;
            used[C[idx]] = 1;
            usednum[mapped[C[idx]]] = 1;
            rc = 1;
        }
        dfs(idx-1, DIV[carry+mapped[A[idx]]+mapped[B[idx]]]);
        if(rc)  used[C[idx]] = 0, usednum[mapped[C[idx]]] = 0;
    } else if(used[A[idx]] && !used[B[idx]]) {
        if(used[C[idx]]) {
            mapped[B[idx]] = MOD[mapped[C[idx]]-carry-mapped[A[idx]]+n];
            if(usednum[mapped[B[idx]]])
                return;
            used[B[idx]] = 1;
            usednum[mapped[B[idx]]] = 1;
            dfs(idx-1, DIV[carry+mapped[A[idx]]+mapped[B[idx]]]);
            used[B[idx]] = 0, usednum[mapped[B[idx]]] = 0;
        } else {
            for(j = 0; j < n; j++) {
                i = V[j];
                mapped[B[idx]] = i, mapped[C[idx]] = MOD[mapped[A[idx]]+i+carry];
                if(usednum[i] || usednum[C[idx]])
                    continue;
                used[B[idx]] = 1, used[C[idx]] = 1;
                usednum[mapped[B[idx]]] = 1, usednum[mapped[C[idx]]] = 1;
                dfs(idx-1, DIV[mapped[A[idx]]+mapped[B[idx]]+carry]);
                used[B[idx]] = 0, used[C[idx]] = 0;
                usednum[mapped[B[idx]]] = 0, usednum[mapped[C[idx]]] = 0;
            }
        }
    } else if(!used[A[idx]] && used[B[idx]]) {
        if(used[C[idx]]) {
            mapped[A[idx]] = MOD[mapped[C[idx]]-carry-mapped[B[idx]]+n];
            if(usednum[mapped[A[idx]]])
                return;
            used[A[idx]] = 1;
            usednum[mapped[A[idx]]] = 1;
            dfs(idx-1, DIV[carry+mapped[A[idx]]+mapped[B[idx]]]);
            used[A[idx]] = 0, usednum[mapped[A[idx]]] = 0;
        } else {
            for(j = 0; j < n; j++) {
                i = V[j];
                mapped[A[idx]] = i, mapped[C[idx]] = MOD[mapped[B[idx]]+i+carry];
                if(usednum[i] || usednum[C[idx]])
                    continue;
                used[A[idx]] = 1, used[C[idx]] = 1;
                usednum[mapped[A[idx]]] = 1, usednum[mapped[C[idx]]] = 1;
                dfs(idx-1, DIV[mapped[A[idx]]+mapped[B[idx]]+carry]);
                used[A[idx]] = 0, used[C[idx]] = 0;
                usednum[mapped[A[idx]]] = 0, usednum[mapped[C[idx]]] = 0;
            }
        }
    } else {
        int k;
        for(k = 0; k < n; k++) {
            i = V[k];
            if(usednum[i])  continue;
            for(j = used[C[idx]] ? MOD[mapped[C[idx]]-i-carry+n] : A[idx] == B[idx] ? i : 0; j < n; j++) {
                if(usednum[j])    continue;
                if(A[idx] != B[idx] && i == j)  continue;
                if(used[C[idx]]) {
                    mapped[A[idx]] = i, mapped[B[idx]] = MOD[mapped[C[idx]]-i-carry+n];
                    if(usednum[mapped[B[idx]]]) break;
                    if(A[idx] == B[idx] && i != mapped[B[idx]]) break;
                    if(A[idx] != B[idx] && i == mapped[B[idx]]) break;
                    used[A[idx]] = 1, used[B[idx]] = 1;
                    usednum[mapped[A[idx]]] = 1, usednum[mapped[B[idx]]] = 1;
                    dfs(idx-1, DIV[i+mapped[B[idx]]+carry]);
                    used[A[idx]] = 0, used[B[idx]] = 0;
                    usednum[mapped[A[idx]]] = 0, usednum[mapped[B[idx]]] = 0;
                    break;
                } else {
                    mapped[A[idx]] = i, mapped[B[idx]] = j, mapped[C[idx]] = MOD[i+j+carry];
                    if(usednum[mapped[C[idx]]])
                        continue;
                    used[A[idx]] = 1, used[B[idx]] = 1, used[C[idx]] = 1;
                    usednum[mapped[A[idx]]] = 1, usednum[mapped[B[idx]]] = 1, usednum[mapped[C[idx]]] = 1;
                    dfs(idx-1, DIV[i+j+carry]);
                    used[A[idx]] = 0, used[B[idx]] = 0, used[C[idx]] = 0;
                    usednum[mapped[A[idx]]] = 0, usednum[mapped[B[idx]]] = 0, usednum[mapped[C[idx]]] = 0;
                }
                if(A[idx] == B[idx])    break;
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    int i;
    for(i = 0; i < 127; i++)
        MOD[i] = i%n, DIV[i] = i/n;
    for(i = 0; i < n; i++)
        V[i] = i;
    for(i = 0; i < 100; i++) {
        int x, y, t;
        x = rand()%n, y = rand()%n;
        t = V[x], V[x] = V[y], V[y] = t;
    }
    scanf("%s %s %s", &A, &B, &C);
    dfs(n-1, 0);
    return 0;
}
