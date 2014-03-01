#include <stdio.h>
int bA[350], bB[350], bC[350];
int bAt, bBt, bCt;
int step;
void print() {
    if(step < 0)
        return;
    int i;
    printf("A=>");
    for(i = 0; i < bAt; i++) {
        if(!i)  printf("  ");
        printf(" %d", bA[i]);
    }
    printf("\nB=>");
    for(i = 0; i < bBt; i++) {
        if(!i)  printf("  ");
        printf(" %d", bB[i]);
    }
    printf("\nC=>");
    for(i = 0; i < bCt; i++) {
        if(!i)  printf("  ");
        printf(" %d", bC[i]);
    }
    puts("\n");
    step--;
}
void move(char st, char ed) {
    if(st == 'A' && ed == 'B')
        bB[bBt++] = bA[--bAt];
    if(st == 'A' && ed == 'C')
        bC[bCt++] = bA[--bAt];
    if(st == 'B' && ed == 'A')
        bA[bAt++] = bB[--bBt];
    if(st == 'B' && ed == 'C')
        bC[bCt++] = bB[--bBt];
    if(st == 'C' && ed == 'A')
        bA[bAt++] = bC[--bCt];
    if(st == 'C' && ed == 'B')
        bB[bBt++] = bC[--bCt];
    print();
}
void hanoi(int n, char A, char B, char C) {
    if(step < 0)    return;
    if(n == 1) {
        move(A, C);
        return ;
    } else{
        hanoi(n - 1, A, C, B);
        move(A, C);
        hanoi(n - 1, B, A, C);
    }
}
int main() {
    int n, cases = 0;
    while(scanf("%d %d", &n, &step) == 2) {
        if(n == 0 && step == 0)
            break;
        printf("Problem #%d\n\n", ++cases);
        bAt = bBt = bCt = 0;
        int i;
        for(i = n; i >= 1; i--)
            bA[bAt++] = i;
        print();
        hanoi(n, 'A', 'B', 'C');
    }
    return 0;
}
