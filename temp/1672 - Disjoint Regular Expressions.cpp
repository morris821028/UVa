#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <list>
using namespace std;
#define MAXN 2048
#define MAXT 32
#define MAXSTATE 65536
const int epsilon = 0;
struct State {
    map<char, vector<State*> > trans;
    int ac, label;
} nodes[MAXSTATE];
struct NFA {
    State *st, *ac;
    NFA() {
        st = ac = NULL;
    }
};
int statesize;
State* getState() {
    State *p;
    p = &nodes[statesize++];
    p->trans.clear();
    p->ac = p->label = 0;
    return p;
}
NFA simpleNFA(char c) {
    NFA ret;
    State *p = getState(), *q = getState();
    ret.st = p, ret.ac = q, q->ac = 1;
    p->trans[c].push_back(q);
    return ret;
}
NFA orNFA(NFA L, NFA R) {
    if (R.st == NULL)
        return L;
    NFA ret;
    State *p = getState(), *q = getState();
    p->trans[epsilon].push_back(L.st);
    p->trans[epsilon].push_back(R.st);
    L.ac->trans[epsilon].push_back(q);
    R.ac->trans[epsilon].push_back(q);
    L.ac->ac = R.ac->ac = 0;
    ret.st = p, ret.ac = q, q->ac = 1;
    return ret;
}
NFA andNFA(NFA L, NFA R) {
    if (R.st == NULL)
        return L;
    NFA ret;
    State *p = getState(), *q = getState();
    p->trans[epsilon].push_back(L.st);
    L.ac->trans[epsilon].push_back(R.st);
    R.ac->trans[epsilon].push_back(q);
    L.ac->ac = R.ac->ac = 0;
    ret.st = p, ret.ac = q, q->ac = 1;
    return ret;
}
NFA starNFA(NFA L) {
    if (L.st == NULL)
        return L;
    NFA ret;
    State *p = getState(), *q = getState();
    p->trans[epsilon].push_back(L.st);
    L.st->trans[epsilon].push_back(L.ac);
    L.ac->trans[epsilon].push_back(L.st);
    L.ac->trans[epsilon].push_back(q);
    L.ac->ac = 0;
    ret.st = p, ret.ac = q, q->ac = 1;
    return ret;
}
NFA parsing(string exp) {
//        puts("parsing");
//        cout << exp << endl;
    if (exp.length() == 0)
        return NFA();
    if (exp.size() == 1) {
//        cout << exp << endl;
        return simpleNFA(exp[0]);
    }
    int l = 0, pos = -1;
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] == '(') {
            l++;
        } else if (exp[i] == ')') {
            l--;
        } else if (exp[i] == '|') {
            if (pos == -1 && l == 0)
                pos = i;
        }
    }
    if (pos != -1) {
        string left = exp.substr(0, pos), right = exp.substr(pos+1);
//        printf("left %s | right %s\n", left.c_str(), right.c_str());
        NFA L, R;
        L = parsing(left);
        R = parsing(right);
        return orNFA(L, R);
    } else {
        string left, right;
        int star = 0;
        if (exp[0] == '(') {
            l = 1;
            for (int i = 1; i < exp.size(); i++) {
                if (exp[i] == '(') {
                    l++;
                } else if (exp[i] == ')') {
                    l--;
                    if (l == 0) {
                        if (i+1 < exp.size() && exp[i+1] == '*') {
                            star = 1;
                            left = exp.substr(1, i-1);
                            right = exp.substr(i+2);
                        } else {
                            left = exp.substr(1, i-1);
                            right = exp.substr(i+1);
                        }
                        break;
                    }
                }
            }
        } else {
            for (int i = 0; i < exp.size(); i++) {
                if (exp[i] == '(') {
                    l++;
                } else if (exp[i] == ')') {
                    l--;
                }
                if (l == 0) {
                    if (i+1 < exp.size() && exp[i+1] == '*') {
                        star = 1;
                        left = exp.substr(0, i+1);
                        right = exp.substr(i+2);
                    } else {
                        left = exp.substr(0, i+1);
                        right = exp.substr(i+1);
                    }
                    break;
                }
            }
        }
        while (right.size() > 0 && right[0] == '*')
            right = right.substr(1);
//        printf("left %s star %d right %s\n", left.c_str(), star, right.c_str());
        NFA L, R;
        L = parsing(left);
        R = parsing(right);
        if (star)
            L = starNFA(L);
        return andNFA(L, R);
    }
}
int relabel(NFA A) {
    int size = 0;
    State *u, *v;
    queue<State*> Q;
    Q.push(A.st), A.st->label = ++size;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (map<char, vector<State*> >::iterator it = u->trans.begin();
             it != u->trans.end(); it++) {
            for (int i = 0; i < it->second.size(); i++) {
                v = it->second[i];
                if (v->label == 0) {
                    v->label = ++size;
                    Q.push(v);
                }
            }
        }
    }
//    assert(size < MAXN);
    return size;
}
int visited[MAXN][MAXN][2];
string inexp[MAXN][MAXN][2];
int intersection(NFA A, NFA B, string &ret) {
    static int cases = 0;
    cases++;
    queue<State*> P, Q;
    queue<int> S;
    State *p, *q, *u, *v;
    int s;
    P.push(A.st), Q.push(B.st), S.push(0);
    visited[A.st->label][B.st->label][0] = cases;
    inexp[A.st->label][B.st->label][0] = "";
    while (!P.empty()) {
        p = P.front(), P.pop();
        q = Q.front(), Q.pop();
        s = S.front(), S.pop();
        string str = inexp[p->label][q->label][s];
        if (p->ac && q->ac && s == 1) {
            if (ret.length() && str.length() >= ret.length())
                continue;
            ret = str;
        }
        if (p->trans.count(epsilon)) {
            vector<State*> &trans = p->trans[epsilon];
            for (int i = 0; i < trans.size(); i++) {
                if (visited[trans[i]->label][q->label][s] != cases) {
                    visited[trans[i]->label][q->label][s] = cases;
                    inexp[trans[i]->label][q->label][s] = str;
                    P.push(trans[i]), Q.push(q), S.push(s);
                } else {
                    if (inexp[trans[i]->label][q->label][s].length() > str.length()) {
                        inexp[trans[i]->label][q->label][s] = str;
                        P.push(trans[i]), Q.push(q), S.push(s);
                    }
                }
            }
        }
        if (q->trans.count(epsilon)) {
            vector<State*> &trans = q->trans[epsilon];
            for (int i = 0; i < trans.size(); i++) {
                if (visited[p->label][trans[i]->label][s] != cases) {
                    visited[p->label][trans[i]->label][s] = cases;
                    inexp[p->label][trans[i]->label][s] = str;
                    P.push(p), Q.push(trans[i]), S.push(s);
                } else {
                    if (inexp[p->label][trans[i]->label][s].length() > str.length()) {
                        inexp[p->label][trans[i]->label][s] = str;
                        P.push(p), Q.push(trans[i]), S.push(s);
                    }
                }
            }
        }
        for (map<char, vector<State*> >::iterator it = p->trans.begin();
             it != p->trans.end(); it++) {
            if (it->first == epsilon)
                continue;
            if (q->trans.count(it->first)) {
                u = it->second[0];
                v = q->trans[it->first][0];
                if (visited[u->label][v->label][1] != cases) {
                    visited[u->label][v->label][1] = cases;
                    inexp[u->label][v->label][1] = str + it->first;
//                    printf("%s %s\n", str.c_str(), inexp[u->label][v->label][1].c_str());
                    P.push(u), Q.push(v), S.push(1);
                } else {
                    if (inexp[u->label][v->label][1].length() > str.length() + 1) {
                        inexp[u->label][v->label][1] = str + it->first;
//                        printf("%s %s\n", str.c_str(), inexp[u->label][v->label][1].c_str());
                        P.push(u), Q.push(v), S.push(1);
                    }
                }
            }
        }
    }
    return ret.length() > 0;
}
int main() {
    char s[MAXN];
    NFA A, B;
    while (scanf("%s", s) == 1) {
        statesize = 0;
        A = parsing(s);
        scanf("%s", s);
        B = parsing(s);
        relabel(A), relabel(B);
        string instr = "";
        int ret = intersection(A, B, instr);
        if (!ret) {
            puts("Correct");
        } else {
            puts("Wrong");
            printf("%s\n", instr.c_str());
        }
    }
    return 0;
}
/*
 a(ab)*b
 a(a|b)*ab
 a(ab)*a
 a(a|b)*ba
 a**
 a*
 (ab)*
 (ba)*
 (a|b*b*b*b*b*b*b*b*b*b*b*)c
 (a|b)*c
 */
