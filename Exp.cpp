#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;
typedef struct {
    int l, r;
    int flag, num;
} Node;
Node Nd[100];
int size;
stringstream sin;
void pre_build(int idx) {
    string tmp;
    sin >> tmp;
    if((tmp[0] > '9' || tmp[0] < '0') && tmp.length() == 1) {
        Nd[idx].num = tmp[0];
        Nd[idx].flag = 0;
        Nd[idx].l = ++size;
        pre_build(size);
        Nd[idx].r = ++size;
        pre_build(size);
    } else {
        stringstream nin;
        nin << tmp;
        nin >> Nd[idx].num;
        Nd[idx].flag = 1;
        Nd[idx].l = Nd[idx].r = 0;
    }
}
void post_build(int idx) {
    string tmp;
    sin >> tmp;
    if((tmp[0] > '9' || tmp[0] < '0') && tmp.length() == 1) {
        Nd[idx].num = tmp[0];
        Nd[idx].flag = 0;
        Nd[idx].r = ++size;
        post_build(size);
        Nd[idx].l = ++size;
        post_build(size);
    } else {
        stringstream nin;
        nin << tmp;
        nin >> Nd[idx].num;
        Nd[idx].flag = 1;
        Nd[idx].l = Nd[idx].r = 0;
    }
}
int priority(string c) {
    switch(c[0]) {
        case '(':return 1;
        case ')':return 2;
        case '+':return 3;
        case '-':return 3;
        case '*':return 4;
        case '/':return 4;
        case '%':return 4;
    }
}
void in_build(string in) {
    string stk[100], post[100], tmp;
    int sIdx = -1, pIdx = -1;
    stringstream bin;
    bin << in;
    while(bin >> tmp) {
        if(!((tmp[0] > '9' || tmp[0] < '0') && tmp.length() == 1))
            post[++pIdx] = tmp;
        else {
            stk[++sIdx] = tmp;
            if(tmp == ")") {
                sIdx--;
                while(sIdx >= 0 && stk[sIdx] != "(")
                    post[++pIdx] = stk[sIdx--];
                sIdx--;
            } else {
                while(sIdx >= 1 && priority(stk[sIdx-1]) >= priority(stk[sIdx])
                        && stk[sIdx] != "(") {
                    post[++pIdx] = stk[sIdx-1];
                    stk[sIdx-1] = stk[sIdx];
                    sIdx--;
                }
            }
        }
    }
    while(sIdx >= 0)    post[++pIdx] = stk[sIdx--];
    while(pIdx >= 0) {
        sin << post[pIdx] << ' ';
        pIdx--;
    }
    post_build(1);
}
double calu(int idx) {
    if(Nd[idx].flag)    return Nd[idx].num;
    switch(Nd[idx].num) {
        case '+':
            return calu(Nd[idx].l)+calu(Nd[idx].r);
        case '-':
            return calu(Nd[idx].l)-calu(Nd[idx].r);
        case '*':
            return calu(Nd[idx].l)*calu(Nd[idx].r);
        default:
            return calu(Nd[idx].l)/calu(Nd[idx].r);
    }
}
void preorder(int idx) {
    if(Nd[idx].flag) {
        printf("%d ", Nd[idx].num);
    } else {
        printf("%c ", Nd[idx].num);
        preorder(Nd[idx].l);
        preorder(Nd[idx].r);
    }
}
void inorder(int idx) {
    if(Nd[idx].flag) {
        printf("%d ", Nd[idx].num);
    } else {
        if(!Nd[Nd[idx].l].flag)
            printf("( ");
        inorder(Nd[idx].l);
        if(!Nd[Nd[idx].l].flag)
            printf(") ");
        printf("%c ", Nd[idx].num);
        if(!Nd[Nd[idx].r].flag)
            printf("( ");
        inorder(Nd[idx].r);
        if(!Nd[Nd[idx].r].flag)
            printf(") ");
    }
}
void postorder(int idx) {
    if(Nd[idx].flag) {
        printf("%d ", Nd[idx].num);
    } else {
        postorder(Nd[idx].l);
        postorder(Nd[idx].r);
        printf("%c ", Nd[idx].num);
    }
}
int main() {
    int ch;
    string line;
    while(scanf("%d", &ch) == 1) {
        cin.ignore(100, '\n');
        getline(cin, line);
        sin.clear();
        size = 1;
        if(ch == 1) {
            sin << line;
            pre_build(1);
        } else if(ch == 2)
            in_build(line);
        else {
            stringstream tmp;
            string stk[100];
            int idx = 0;
            tmp << line;
            while(tmp >> stk[idx])
                idx++;
            idx--;
            while(idx >= 0) {
                sin << stk[idx] << ' ';
                idx--;
            }
            post_build(1);
        }
        printf("preorder : ");
            preorder(1);
        puts("");
        printf("inorder  : ");
            inorder(1);
        puts("");
        printf("postorder: ");
            postorder(1);
        puts("");
        printf(" = %.2lf\n", calu(1));
    }
    return 0;
}
