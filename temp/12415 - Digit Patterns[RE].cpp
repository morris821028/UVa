// runtime error
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
#define MAXN 32767
#define MAXS 10000005
#define MAXSTATE 32767
#define MAXT 11
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
struct DFA {
public:
    int N, st;
    int trans[MAXN][MAXT], ac[MAXN];
    DFA() {}
    DFA(const NFA &A, char alphaBegin, char alphaEnd) {
        st = 0;
        memset(ac, 0, sizeof(st));
        memset(trans, -1, sizeof(trans));
        build(A, alphaBegin, alphaEnd);
    }
    vector<State*> getSetOf(vector<State*> setOfStates, char c) {
        set<State*> h;
        vector<State*> ret;
        queue<State*> Q;
        State *u;
        for (int i = 0; i < setOfStates.size(); i++) {
            u = setOfStates[i];
            if (u->trans.count(c)) {
                vector<State*> trans = u->trans[c];
                for (int j = 0; j < trans.size(); j++) {
                    if (!h.count(trans[j])) {
                        h.insert(trans[j]);
                        ret.push_back(trans[j]);
                    }
                }
            }
        }
        sort(ret.begin(), ret.end());
        return getClosure(ret);
    }

    vector<State*> getClosure(vector<State*> setOfStates) {
        set<State*> h;
        vector<State*> ret;
        queue<State*> Q;
        State *u;
        for (int i = 0; i < setOfStates.size(); i++) {
            u = setOfStates[i];
            h.insert(u), Q.push(u);
        }
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            ret.push_back(u);
            vector<State*> trans = u->trans[epsilon];
            for (int i = 0; i < trans.size(); i++) {
                if (!h.count(trans[i])) {
                    h.insert(trans[i]);
                    Q.push(trans[i]);
                }
            }
        }
        sort(ret.begin(), ret.end());
        return ret;
    }
    void build(const NFA &A, char alphaBegin, char alphaEnd) {
        vector< vector<State*> > T;
        vector<State*> initState = getClosure(vector<State*>(1, A.st));
        map< vector<State*>, int> R;
        int label = -1;
        T.push_back(initState), R[initState] = ++label;
        st = R[initState];
        for (int i = 0; i < T.size(); i++) {
            int x = i, y, v = 0;
            for (int j = 0; j < T[i].size(); j++)
                v |= T[i][j]->ac;
            ac[x] = v;
            for (int j = alphaBegin; j <= alphaEnd; j++) {
                vector<State*> nextState = getSetOf(T[i], j);
                if (nextState.size() == 0)
                    continue;
                if (!R.count(nextState)) {
                    R[nextState] = ++label;
                    T.push_back(nextState);
                }
                y = R[nextState];
                trans[x][j - alphaBegin] = y;
            }
        }
        N = (int) T.size();
    }
} dfa;
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
    if (exp.length() == 0)
        return NFA();
    if (exp.size() == 1) {
        return simpleNFA(exp[0]);
    }
    int l = 0, pos = -1;
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] == '(') {
            l++;
        } else if (exp[i] == ')') {
            l--;
        } else if (exp[i] == '+') {
            if (pos == -1 && l == 0)
                pos = i;
        }
    }
    if (pos != -1) {
        string left = exp.substr(0, pos), right = exp.substr(pos+1);
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
//                printf("%d -> %d %c\n", u->label, v->label, it->first);
            }
        }
    }
    assert(size < MAXN);
    return size;
}
char s[MAXS], ret[MAXS];
NFA nfa;
int main() {
    int N;
    while (scanf("%d %s", &N, s) == 2) {
        statesize = 0;
        nfa = parsing(s);
        relabel(nfa);
        dfa = DFA(nfa, '0', '0' + N);
        scanf("%s", s);
        int slen = (int) strlen(s);
        vector<int> ac;
        for (int i = 0; i < dfa.N; i++) {
            if (dfa.ac[i])
                ac.push_back(i);
        }
        for (int i = 0; i < slen; i++) {
            ret[i] = 0;
        }
        for (int i = 0; i < slen; i++) {
            for (int j = i, k = dfa.st; j < slen && k != -1; j++) {
                k = dfa.trans[k][s[j] - '0'];
                if (k != -1 && dfa.ac[k])
                    ret[j] = 1;
            }
        }
        
        int f = 0;
        for (int i = 0; i < slen; i++) {
            if (ret[i]) {
                if (f)  putchar(' ');
                f = 1;
                printf("%d", i + 1);
            }
        }
        puts("");
    }
    return 0;
}
/*
 6 1(2+3)*4
 012345
 2 00*(10+100)*
 00100
 10 ((((02)((9))+(((50(((((0)836))))+((6+5+(7881+4)))(((((93)(((3(7))(8+2)3))70))))))((9((8)*))((7)+65((66(7))+(6)))((0))977+(093)2((3)+6)2(5)8)))))(((0)+5(38)+47))
 97
 10 ((56(9)*))(4+(3+1+9)(23*28)((8)(7)45*))(0)+((((4(4)3(4*))+(((((((3)40((((7*(0)0)))*)((4))+(((8))(0)73)(6)+1))(1)(1(((50))56))+((((437))8+6(((1)))9+599+2(23)))))*)))))
 86
 */
