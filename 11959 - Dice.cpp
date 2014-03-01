#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int dice[6];
} DICE;
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
int cmp(const void *a, const void *b) {
    static DICE *i, *j;
    static int k;
    i = (DICE *)a, j = (DICE *)b;
    for(k = 0; k < 6; k++)
        if(i->dice[k] != j->dice[k])
            return i->dice[k] - j->dice[k];
    return 0;
}

DICE Spin_dice(DICE& A) {
    static int i, j;
    DICE B = A;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(cmp(&B, &A) > 0)
                B = A;
            clockwise(&A);
        }
        Right_turn(&A);
    }
    Up_turn(&A);
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 4; j++) {
            if(cmp(&B, &A) > 0)
                B = A;
            clockwise(&A);
        }
        Up_turn(&A), Up_turn(&A);
    }
    return B;
}
main() {
    int n, i;
    DICE A, B;// 前右上後左下
    char a[20], b[20]; // 上下前左後右
    scanf("%d", &n);
    while(n--) {
        scanf("%s %s", a, b);
        A.dice[0] = a[2];
        A.dice[1] = a[5];
        A.dice[2] = a[0];
        A.dice[3] = a[4];
        A.dice[4] = a[3];
        A.dice[5] = a[1];

        B.dice[0] = b[2];
        B.dice[1] = b[5];
        B.dice[2] = b[0];
        B.dice[3] = b[4];
        B.dice[4] = b[3];
        B.dice[5] = b[1];
        A = Spin_dice(A);
        B = Spin_dice(B);
        for(i = 0; i < 6; i++)
            if(A.dice[i] != B.dice[i])
                break;
        if(i == 6)
            puts("Equal");
        else
            puts("Not Equal");
    }
    return 0;
}
