#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <vector>
#define eps 1e-6
using namespace std;
struct ND {
    int l, r, ptr;
    string token;
    double p;
    void set(int a, int b, int c, string d, double e) {
        l = a, r = b, ptr = c;
        token = d;
        p = e;
    }
};
struct cmp {
    bool operator() (ND a, ND b) {
        return a.p > b.p;
    }
};
ND nd[1024];
char buf[128];
map<string, string> hufcode;
void dfs(int idx, int dep) {
    if(!idx)    return;
    buf[dep] = '0';
    dfs(nd[idx].l, dep+1);
    buf[dep] = '1';
    dfs(nd[idx].r, dep+1);
    if(!nd[idx].l) {
        buf[dep] = '\0';
        hufcode[nd[idx].token] = buf;
    }
}
int main() {
    puts("Input data (seperate by space):");
    string line, token;
    getline(cin, line);
    stringstream sin(line);
    int size = 0, i;
    double p, sump = 0;
    priority_queue<ND, vector<ND>, cmp> pQ;
    ND L, R;
    while(sin >> token >> p) {
        ++size;
        nd[size].set(0, 0, size, token, p);
        sump += p;
        pQ.push(nd[size]);
    }
    if(fabs(sump-1) > eps) {
        puts("The sum of frequency is not equal to 1");
        system("pause");
        return 0;
    }
    while(pQ.size() >= 2) {
        L = pQ.top(), pQ.pop();
        R = pQ.top(), pQ.pop();
        ++size;
        nd[size].set(L.ptr, R.ptr, size, "", L.p+R.p);
        pQ.push(nd[size]);
    }
    dfs(size, 0);
    for(map<string, string>::iterator it = hufcode.begin();
        it != hufcode.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
    system("pause");
    return 0;
}
/*
a 0.10 b 0.15 c 0.30 d 0.16 e 0.29
a 0.8 b 0.12 c 0.42
a 0.2 c 0.2 d 0.2 b 0.2 e 0.2
a 0.49999999999 b 0.50000000001
a -1 b 2
ab 1 c 0
a 1 a 0
*/
