#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;

struct Argus {
    int ID, p, v;
};
struct cmp {
    bool operator() (Argus a, Argus b) {
        if(a.v != b.v)
            return a.v > b.v;
        return a.ID > b.ID;
    }
};

int main() {
    priority_queue<Argus, vector<Argus>, cmp> Q;
    char str[50];
    int ID, p, k;
    Argus tmp;
    while(scanf("%s", str) == 1) {
        if(str[0] == '#')
            break;
        scanf("%d %d", &ID, &p);
        tmp.ID = ID, tmp.p = tmp.v = p;
        Q.push(tmp);
    }
    scanf("%d", &k);
    while(k--) {
        printf("%d\n", Q.top().ID);
        tmp = Q.top();
        Q.pop();
        tmp.v += tmp.p;
        Q.push(tmp);
    }
    return 0;
}
