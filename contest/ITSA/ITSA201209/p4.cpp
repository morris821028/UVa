#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;
typedef struct {
    int l, r;
    int num;
    int flag;
} Node;
Node Nd[1000];
int size;
stringstream sin;
void build(int idx) {
    string tmp;
    sin >> tmp;
    if(tmp[0] > '9' || tmp[0] < '0' &&) {
        Nd[idx].num = tmp[0];
        Nd[idx].flag = 0;
        size++;
        Nd[idx].l = size;
        build(size);
        size++;
        Nd[idx].r = size;
        build(size);
    } else {
        stringstream nin;
        nin << tmp;
        int v;
        nin >> v;
        Nd[idx].num = v;
        Nd[idx].flag = 1;
    }
}
void travel(int idx) {
    if(!Nd[idx].flag) {
        if(!Nd[Nd[idx].l].flag)
            printf("(");
        travel(Nd[idx].l);
        if(!Nd[Nd[idx].l].flag)
            printf(")");
    if(Nd[idx].num == '+') {
        printf("+");
    } else
    if(Nd[idx].num == '*') {
        printf("*");
    } else
    if(Nd[idx].num == '/') {
        printf("/");
    } else {
        printf("-");
    }
        if(!Nd[Nd[idx].r].flag)
        printf("(");
        travel(Nd[idx].r);
        if(!Nd[Nd[idx].r].flag)
            printf(")");
    } else {
        printf("%d", Nd[idx].num);
    }
}
double calu(int idx) {
    if(Nd[idx].flag)
        return Nd[idx].num;
    if(Nd[idx].num == '+') {
        return calu(Nd[idx].l)+calu(Nd[idx].r);
    } else
    if(Nd[idx].num == '*') {
        return calu(Nd[idx].l)*calu(Nd[idx].r);
    } else
    if(Nd[idx].num == '/') {
        return calu(Nd[idx].l)/calu(Nd[idx].r);
    } else {
        return calu(Nd[idx].l)-calu(Nd[idx].r);
    }
}
int main() {
    int t;
    scanf("%d", &t);
    getchar();
    string line;
    while(t--) {
        getline(cin, line);
        memset(Nd, 0, sizeof(Nd));
        sin.clear();
        sin << line;
        size = 1;
        build(1);
        travel(1);
        printf("=%.2lf\n", calu(1));
    }
    return 0;
}
