#include<stdio.h>
#define N 8
struct segment {
    int l, r, m;
    int boolt, xort, endt;
} tree[2*N + 20];
void init (int l, int r, int k) {
    tree[k].l = l, tree[k].r = r;
    tree[k].m = (l + r) >> 1;
    tree[k].boolt = 0, tree[k].endt = 1;
    if(l == r) return ;
    init(l, tree[k].m, k<<1);
    init(tree[k].m+1, r, (k<<1)+1);
}
void element_calc(int k) {
    if(tree[k].endt) {
        tree[k].endt = 0;
        tree[(k<<1)].endt = tree[(k<<1)+1].endt = 1;
        tree[(k<<1)].xort = tree[(k<<1)+1].xort = 0;
        tree[(k<<1)].boolt = tree[(k<<1)+1].boolt = tree[k].boolt;
    }
    if(tree[k].xort) {
        tree[k].xort = 0;
        tree[(k<<1)].xort ^= 1;
        tree[(k<<1)+1].xort ^= 1;
    }
}
void modify(int k, int l, int r, int c) {
    if(l <= tree[k].l && r >= tree[k].r) {
        tree[k].xort = 0, tree[k].endt = 1;
        tree[k].boolt = c;
        return ;
    }
    
    element_calc(k);
    if(r <= tree[k].m)  modify(k<<1, l, r, c);
    else if(l > tree[k].m) modify((k<<1)+1, l, r, c);
    else    modify(k<<1, l, tree[k].m, c), modify((k<<1)+1, tree[k].m+1, r, c);
}
void modify_xor(int k, int l, int r) {
    if(l <= tree[k].l && r >= tree[k].r) {
        tree[k].xort ^= 1;
        return ;
    }
    
    element_calc(k);
    if(r <= tree[k].m)  modify_xor(k<<1, l, r);
    else if(l > tree[k].m) modify_xor((k<<1)+1, l, r);
    else    modify_xor(k<<1, l, tree[k].m), modify_xor((k<<1)+1, tree[k].m+1, r);
}
int Ans[2*N][2], At = 0;
void search(int k) {
    element_calc(k);
    if(tree[k].endt) {
        tree[k].boolt ^= tree[k].xort;         
        if(tree[k].boolt)
            Ans[At][0] = tree[k].l, Ans[At][1] = tree[k].r, At++;
    }
    if(tree[k].l == tree[k].r) {
        return ;
    }
    search((k<<1));
    search((k<<1)+1);
}
void Print(int k) {
    element_calc(k);
    if(tree[k].l == tree[k].r) {
        printf("%d", tree[k].boolt);
        return ;
    }
    Print((k<<1));
    Print((k<<1)+1);
}
void Output() {
    if(At == 0)
        {puts("empty set"); return ;}
    int a;
    for(a = 1; a < At; a++) {
        if(Ans[a][0] == Ans[a-1][1] + 1)
            Ans[a][0] = Ans[a-1][0];
        else { 
            printf("(%d,%d) ", Ans[a-1][0] >> 1, (Ans[a-1][1]+1) >> 1);
        } 
    }
    printf("(%d,%d) ", Ans[At-1][0], Ans[At-1][1]);
    puts("");
}
main() {
    char op[2], t1, t2;
    int i, j;
    init(0, N, 1);
    while(scanf("%s %c%d,%d%c", op, &t1, &i, &j, &t2) == 5) {
        if(t1 == '(')   i++;
        if(t2 == ')')   j--;
        switch(op[0]) {
            case 'U': modify(1, i, j, 1); break;/*modify -> 1*/
            case 'I':
                if(i)   modify(1, 0, i - 1, 0);/*modify -> 0*/
                if(j < N) modify(1, j + 1, N, 0);/*modify -> 0*/
                break;
            case 'D': modify(1, i, j, 0); break;
            case 'C':
                if(i)   modify(1, 0, i - 1, 0);
                if(j < N) modify(1, j + 1, N, 0);
                modify_xor(1, i, j);
                break;
            case 'S': modify_xor(1, i, j); break;
        }
        Print(1);puts("");
    }
    search(1);
    Output();
    return 0;
}
