#include <stdio.h>
struct seg {
    int l, r;
    seg *next;
};
seg *head, *tail;
void init(int p) {
    head = new seg;
    tail = head;
    head->l = 1, head->r = p;
    head->next = NULL;
}
void delQ() {
    seg *prev;
    while(head) {
        prev = head;
        head = head->next;
        delete prev;
    }
}
void Noperator() {
    printf("%d\n", head->l);
    if(head->l == head->r) {
        tail->next = head;
        tail = head;
        head = head->next;
        tail->next = NULL;
    } else {
        seg *p = new seg;
        p->l = p->r = head->l;
        head->l++;
        tail->next = p;
        tail = p;
        tail->next = NULL;
    }
}
void Eoperator(int x) {
    if(x == head->l)
        return;
    seg *p, *q;
    p = head, q = NULL;
    while(x < p->l || x > p->r)
        q = p, p = p->next;
    if(p->l == x && x == p->r) { // move 1 block
        q->next = p->next;
        p->next = head;
        head = p;
        if(tail == p)
            tail = q;
        return;
    }
    if(p->l == x) { // split 2 block
        p->l++;
    } else if(p->r == x) { // split 2 block
        p->r--;
    } else { // split 3 block
        q = new seg;
        q->l = x+1;
        q->r = p->r;
        q->next = p->next;
        p->next = q;
        p->r = x-1;
        if(p == tail)
            tail = q;
    }
    q = new seg;
    q->l = q->r = x;
    q->next = head;
    head = q;
}
void printQ() {
    seg *p = head;
    while(p) {
        printf("(%d %d)", p->l, p->r);
        p = p->next;
    }
    printf("*%d %d*", tail->l, tail->r);
    puts("");
}
int main() {
    int P, C, x, cases = 0;
    char cmd[10];
    while(scanf("%d %d", &P, &C) == 2 && P) {
        init(P);
        printf("Case %d:\n", ++cases);
        while(C--) {
            scanf("%s", cmd);
            if(cmd[0] == 'N')
                Noperator();
            else {
                scanf("%d", &x);
                Eoperator(x);
            }
            //printQ();
        }
        delQ();
    }
    return 0;
}
/*
5 6
E 2
N
N
N
N
N
45 15
N
N
N
N
E 13
N
N
E 39
N
N
N
N
N
E 4
N
9 12
N
N
N
E 2
N
E 2
N
E 3
N
E 8
N
N
0 0
*/
