#include<stdio.h>
int Vi[500][1000], Vd[500][1000], Vn[500];
int check(int k) {
    int a, In1, In2, s;
    for(a = 0; a < k; a++) {
        In1 = 0, In2 = 0, s = 0;
        while(In1 < Vn[a] && In2 < Vn[k]) {
            if(Vi[a][In1] < Vi[k][In2]) In1++;
            else if(Vi[a][In1] > Vi[k][In2])    In2++;
            else
                s += (Vd[a][In1++]*Vd[k][In2++]);
        }
        if(s)   return (k&1) + 1;
    }
    return 0;
}
main() {
    int n, m, a, b;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0) break;
        int flag = 0;
        for(a = 0; a < m; a++) {
            scanf("%d", &Vn[a]);
            for(b = 0; b < Vn[a]; b++)
                scanf("%d:%d", &Vi[a][b], &Vd[a][b]);
            if(flag == 0)   flag = check(a);
        }
        switch(flag) {
            case 0: puts("Hakuna matata"); break;
            case 1: puts("Yin"); break;
            case 2: puts("Rofu"); break;
        }
    }
    return 0;
}
