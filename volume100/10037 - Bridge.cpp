#include<stdio.h>
#include<stdlib.h>
int Line[1001] = {};
short Index1, Index2;
short Findback() {
    while(1) {
        if(Line[Index1]) {
            Line[Index1] --;
            return Index1;
        }
        else Index1--;
    }
}
short Findnext() {
    while(1) {
        if(Line[Index2]) {
            Line[Index2] --;
            return Index2;
        }
        else Index2++;
    }
}
main() {
    int N, T, a, x;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &N);
        for(a = 0, Index1 = 1000, Index2 = 0; a < N; a++) {
            scanf("%d", &x);
            Line[x]++;
        }
        int time = 0;
        int t1, t2, Min1 = Findnext(), Min2 = Findnext(), Y, Z;
        int ans[20000][2], at[20000], att = 0;
        while(N > 3) {
            Z = Findback(), Y = Findback();
            t1 = Min2 + Min1 + Z + Min2;/*1. AB + A + YZ + B*/
            t2 = Z + Min1 + Y + Min1;/*2. AZ + A + AY + A*/
            if(t1 < t2) {
                at[att] = 2;
                ans[att][0] = Min1, ans[att][1] = Min2;
                att++;
                at[att] = 1;
                ans[att][0] = Min1;
                att++;
                at[att] = 2;
                ans[att][0] = Y, ans[att][1] = Z;
                att++;
                at[att] = 1;
                ans[att][0] = Min2;
                att++;
            } else {
                at[att] = 2;
                ans[att][0] = Min1, ans[att][1] = Z;
                att++;
                at[att] = 1;
                ans[att][0] = Min1;
                att++;
                at[att] = 2;
                ans[att][0] = Min1, ans[att][1] = Y;
                att++;
                at[att] = 1;
                ans[att][0] = Min1;
                att++;
            }
            time += (t1 < t2)? t1 : t2;
            N -= 2;
        }
        if(N == 2) {
                at[att] = 2;
                ans[att][0] = Min1, ans[att][1] = Min2;
                att++;
            time += Min2;
        } else if(N == 3) {
            Z = Findnext();
                at[att] = 2;
                ans[att][0] = Min1, ans[att][1] = Min2;
                att++;
                at[att] = 1;
                ans[att][0] = Min1;
                att++;
                at[att] = 2;
                ans[att][0] = Min1, ans[att][1] = Z;
                att++;
            time += Min1 + Min2 + Z;
        }
        else if(N == 1) {
                at[att] = 1;
                ans[att][0] = Min1;
                att++;
            time += Min1;
        }
        printf("%d\n", time);
        for(a = 0; a < att; a++) {
            if(at[a] == 1)
                printf("%d\n", ans[a][0]);
            else
                printf("%d %d\n", ans[a][0], ans[a][1]);
        }
        if(T)
            puts("");
    }
    return 0;
}
