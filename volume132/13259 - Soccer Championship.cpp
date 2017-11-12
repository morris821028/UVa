#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits.h>
using namespace std;
struct Record {
    string l, r;
    int lc, rc;
    Record(string l="", string r="", int lc=0, int rc=0):
    l(l), r(r), lc(lc), rc(rc) {}
};

void stat(vector<Record> &R) {
    struct Entry {
        int pt, diff, mx, vis_mx;
        Entry() {pt = mx = vis_mx = 0; diff = 0;}
        void update(int a, int b, int isvis) {
            if (a > b) pt += 3;
            else if (a == b) pt++;
            diff += a - b;
            mx += a;
            if (isvis)
                vis_mx += a;
        }
        bool operator<(const Entry &x) const {
            if (pt != x.pt)
                return pt > x.pt;
            if (diff != x.diff)
                return diff > x.diff;
            if (mx != x.mx)
                return mx > x.mx;
            return vis_mx > x.vis_mx;
        }
    };
    struct StrMap {
        map<string, int> str2int;
        vector<string> str;
        int get(string &s) {
            auto it = str2int.find(s);
            if (it != str2int.end())
                return it->second;
            int &ret = str2int[s];
            ret = (int) str.size();
            str.push_back(s);
            return ret;
        }
        int size() {
            return (int) str.size();
        }
    } smap;
    vector<Entry> table(R.size()*2, Entry());
    for (Record &e : R) {
        int l = smap.get(e.l);
        int r = smap.get(e.r);
        table[l].update(e.lc, e.rc, 0);
        table[r].update(e.rc, e.lc, 1);
    }
    
    int n = smap.size();
    vector<pair<Entry, string>> ret(n);
    for (int i = 0; i < n; i++)
        ret[i] = {table[i], smap.str[i]};
    sort(ret.begin(), ret.end());
    vector<int> idx_rank(n);
    for (int i = 0; i < n; i++)
        idx_rank[smap.get(ret[i].second)] = i;
    
    int paradox = 0;
    for (Record &e : R) {
        if (e.lc == e.rc)
            continue;
        int l = smap.get(e.l);
        int r = smap.get(e.r);
        if (e.lc > e.rc) {
            paradox += idx_rank[l] > idx_rank[r];
        } else {
            paradox += idx_rank[l] < idx_rank[r];
        }
    }
    printf("The paradox occurs %d time(s).\n", paradox);
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, ret[i].second.c_str());
//        printf(" %d %d %d %d\n", ret[i].first.pt, ret[i].first.diff, ret[i].first.mx, ret[i].first.vis_mx);
    }
}
int main() {
    int n;
    static char s[65536];
    while (scanf("%d", &n) == 1) {
        while (getchar() != '\n');
        
        vector<Record> R;
        for (int i = 0; i < n; i++) {
            fgets(s, 65536, stdin);
            vector<string> tks;
            stringstream sin(s);
            string token;
            while (sin >> token)
                tks.push_back(token);
            int vs_pos = -1;
            for (int j = 0; j < tks.size(); j++) {
                if (tks[j] == "vs.") {
                    vs_pos = j;
                    break;
                }
            }
            
            string Ls = "", Rs = "";
            int lc, rc;
            sscanf(tks[vs_pos-1].c_str(), "%d", &lc);
            sscanf(tks[vs_pos+1].c_str(), "%d", &rc);
            for (int i = 0; i < vs_pos-1; i++) {
                Ls = Ls + tks[i];
                if (i != vs_pos-2)
                    Ls += " ";
            }
            for (int i = vs_pos+2; i < tks.size(); i++) {
                Rs = Rs + tks[i];
                if (i != tks.size()-1)
                    Rs += " ";
            }
            R.push_back(Record(Ls, Rs, lc, rc));
        }
        
        stat(R);
    }
    return 0;
}
/*
13
B. DORTMUND 2 vs. 2 REAL MADRID
SP. PORTUGAL 2 vs. 0 LEGIA
SP. PORTUGAL 1 vs. 2 B. DORTMUND
REAL MADRID 5 vs. 1 LEGIA
B. DORTMUND 1 vs. 0 SP. PORTUGAL
LEGIA 3 vs. 3 REAL MADRID
MONACO 3 vs. 0 CSKA M.
SP. PORTUGAL 1 vs. 2 REAL MADRID
B. DORTMUND 8 vs. 4 LEGIA
REAL MADRID 2 vs. 2 B. DORTMUND
LEGIA 1 vs. 0 SP. PORTUGAL
MONACO 1 vs. 0 SP. PORTUGAL
CSKA M. 1 vs. 0 B. DORTMUND
2
TEAM 1 4 vs. 2 TEAM 2
TEAM 2 2 vs. 0 TEAM 1
*/
