#include <stdio.h>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
string sigma[50]; // default 50 kinds
vector<int> g[50][50]; // g[i][j], i : state, j : alpha
bool expandState(set<int> &s, int m, bool acceptTable[]) { // add all state by lembda
    int i, idx;
    bool accept = false;
    for(i = 0; i < m; i++)
        if(sigma[i] == "l") // find lembda index in sigma
            idx = i;
    do {
        bool flag = false;
        for(set<int>::iterator it = s.begin(); it != s.end(); it++) {
            for(vector<int>::iterator jt = g[*it][idx].begin();
                jt != g[*it][idx].end(); jt++) {
                if(s.find(*jt) == s.end()) {
                    flag = true; // update flag;
                    s.insert(*jt);
                }
            }
            accept |= acceptTable[*it];
        }
        if(flag == false) // expandState end
            return accept;
    } while(true);
    return accept;
}
void printState(set<int> &s, bool accept) {
    putchar('(');
    if(accept)
        putchar('*');
    bool firstflag = true;
    for(set<int>::iterator it = s.begin();
        it != s.end(); it++) {
        if(!firstflag)  putchar(',');
        firstflag = false;
        printf("%d", *it);
    }
    putchar(')');
}
int main() {
    string sigmaLine, line;
    getline(cin, sigmaLine);
    //<parse sigma>
    int sigmaSize = 0;
    for(int i = 1, j = sigmaLine.length(); i < j; i++) {
        char buf[50], *p = buf;
        while(sigmaLine[i] != ',' && sigmaLine[i] != ')')
            *p = sigmaLine[i], p++, i++;
        if(sigmaLine[i] == ')')
            break; // don't process last number
        *p = '\0';
        sigma[sigmaSize++] = buf;
    }
    //</parse sigma>
    //debug
    //for(int i = 0; i < sigmaSize; i++)
    //    cout << sigma[i] << endl;
    //debug
    int statei = 1;
    bool acceptTable[50] = {};
    //<parse state link>
    while(getline(cin, line)) {
        int sigmai = -1, num = 0;
        bool accept = false;
        for(int i = 0, j = line.length(); i < j; i++) {
            if(line[i] == '(')
                sigmai++;
            else if(line[i] == '*')
                accept = true; // state (i) acceptable
            else {
                if(line[i] == ',' || line[i] == ')') {
                    if(num) {
                        //debug
                        //printf("%d %s -> %d\n", statei, sigma[sigmai].c_str(), num);
                        //debug
                        g[statei][sigmai].push_back(num);
                    }
                    num = 0;
                } else
                    num = num*10 + line[i]-'0';
            }
        }
        acceptTable[statei] = accept;
        statei++;
    }
    int stateSize = statei;
    //</parse state link> windows using Ctrl+Z, linux using Ctrl+D (EOF)
    set<int> newState[50]; // default newState max 50
    bool newacceptTable[50] = {};
    vector<int> newg[50][50]; // new table to transtate
    int newStateSize = 1;
    newState[0].insert(1); // start state = 1
    newacceptTable[0] = expandState(newState[0], sigmaSize, acceptTable);
    putchar('(');
    for(int i = 0, j = 1; i < sigmaSize; i++) {
        if(sigma[i] == "l")
            continue;
        if(!j)  putchar(',');
        j = 0;
        printf("%s", sigma[i].c_str());
    }
    putchar(')');
    puts("");
    for(int i = 0; i < newStateSize; i++) {
        printState(newState[i], newacceptTable[i]);
        for(int j = 0; j < sigmaSize; j++) {
            if(sigma[j] == "l")
                continue;
            set<int> trans;
            for(set<int>::iterator it = newState[i].begin();
                it != newState[i].end(); it++) {
                for(vector<int>::iterator jt = g[*it][j].begin();
                    jt != g[*it][j].end(); jt++)
                    trans.insert(*jt);
            }
            bool accept = expandState(trans, sigmaSize, acceptTable);
            if(trans.size() == 0) {
                printf("(0)"); // NULL
                continue;
            }
            int node = -1; // find new state exists in newState?
            for(int p = 0; p < newStateSize; p++) {
                if(newState[p].size() != trans.size())
                    continue;
                bool same = true;
                for(set<int>::iterator it = newState[p].begin(), jt = trans.begin();
                    it != newState[p].end(); it++, jt++) {
                    if(*it !=  *jt) {
                        same = false;
                        break;
                    }
                }
                if(same == true) {
                    node = p;
                    continue;
                }
            }
            if(node < 0) {
                newState[newStateSize] = trans; // copy set
                newacceptTable[newStateSize] = accept;
                node = newStateSize++;
            }
            printState(newState[node], newacceptTable[node]);
        }
        puts("");
    }
    return 0;
}
/*
(l,a,b,2)
(2,0)(3,0)(0,0)
(0,0)(4,5)(0,0)
(0,0)(0,0)(4,0)
(0,0)(5,0)(5,0)
(*,*)(*,*)(*,*)

(l,a,b,2)
(3,0)(4,0)(0,0)
(0,0)(3,1)(2,0)
(2,0)(0,0)(4,0)
(3,*)(4,*)(*,*)
*/
