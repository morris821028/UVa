#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int dice[6];
}DICE;
void Right_turn(DICE *A) {
    static int t;
    t = A->dice[0], A->dice[0] = A->dice[4];
    A->dice[4] = A->dice[3], A->dice[3] = A->dice[1], A->dice[1] = t;
}
void Up_turn(DICE *A) {
    static int t;
    t = A->dice[0], A->dice[0] = A->dice[5];
    A->dice[5] = A->dice[3], A->dice[3] = A->dice[2], A->dice[2] = t;
}
void clockwise(DICE *A) {
    static int t;
    t = A->dice[2], A->dice[2] = A->dice[4];
    A->dice[4] = A->dice[5], A->dice[5] = A->dice[1], A->dice[1] = t;
}
DICE D[1000];
int store = 0;
int cmp(const void *a, const void *b) {
    static DICE *i, *j;
    static int k;
    i = (DICE *)a, j = (DICE *)b;
    for(k = 0; k < 6; k++)
        if(i->dice[k] != j->dice[k])
            return i->dice[k] - j->dice[k];
    return 0;
}
void Print(DICE A) {
    static int i;
    for(i = 0; i < 6; i++)
        printf("%d ", A.dice[i]);
    puts("");
}
void Spin_dice(DICE A) {
    static int i, j;
    D[store] = A;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
                D[store++] = A;
            clockwise(&A);
        }
        Right_turn(&A);
    }
    Up_turn(&A);
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 4; j++) {
            D[store++] = A;
            clockwise(&A);
        }
        Up_turn(&A), Up_turn(&A);
    }
}
main() {
    int n, i, j, v, nd;
    char str[10];
    DICE A;
    scanf("%d", &n);
    while(n--) {
        store = 0;
        for(i = 0; i < 6; i++) {
            scanf("%s %d", str, &v);
            nd = (str[0]-'A')+(str[1]-'0')*3;
            A.dice[nd] = v;
        }
        Spin_dice(A);
        int ans = 0;
        for(i = 0; i < store; i++) {
            int t[24];
            t[0] = D[i].dice[0]+D[i].dice[1]*2+D[i].dice[2]*2+D[i].dice[3]*2+D[i].dice[4]+D[i].dice[5]*2;
            t[1] = D[i].dice[0]*4+D[i].dice[1]+D[i].dice[2]*2+D[i].dice[3]+D[i].dice[4]+D[i].dice[5];
            t[2] = D[i].dice[0]*2+D[i].dice[1]+D[i].dice[2]*3+D[i].dice[3]+D[i].dice[4]+D[i].dice[5]*2;
            t[3] = D[i].dice[0]*2+D[i].dice[1]+D[i].dice[2]*2+D[i].dice[3]*2+D[i].dice[4]+D[i].dice[5]*2;
            t[4] = D[i].dice[0]*3+D[i].dice[1]+D[i].dice[2]*3+D[i].dice[3]+D[i].dice[4]+D[i].dice[5];
            t[5] = D[i].dice[0]+D[i].dice[1]*2+D[i].dice[2]*2+D[i].dice[3]*2+D[i].dice[4]*2+D[i].dice[5];
            t[6] = D[i].dice[0]*2+D[i].dice[1]+D[i].dice[2]*4+D[i].dice[3]+D[i].dice[4]+D[i].dice[5];
            t[7] = D[i].dice[0]+D[i].dice[1]*2+D[i].dice[2]+D[i].dice[3]*2+D[i].dice[4]*2+D[i].dice[5]*2;
            for(j = 0; j < 7; j++) {
                if(t[j] > ans)
                    ans = t[j];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
