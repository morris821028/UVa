#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
using namespace std;

string divideString(string u, int div) {
    char s[1024] = {};
    int num = 0;
    for (int i = 0; i < u.length(); i++) {
        num = num * 10 + u[i] - '0';
        s[i] = num/div + '0', num %= div;
    }
    int idx = s[0] == '0' ? 1 : 0;
    string v = s + idx;
    return v;
}
string removePos(string u, int pos, int items = 1) {
    string v = u.substr(0, pos) + u.substr(pos + items);
//    cout << u << ", " << pos <<" = " << v<< endl;
    if (v.length() == 0)
        return "0";
    return v;
}
int numicStringCompare(string u, string v) {
    if (u.length() != v.length())
        return u.length() < v.length();
    for (int i = 0; i < u.length(); i++) {
        if (u[i] != v[i])
            return u[i] < v[i];
    }
    return 0;
}

int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        char s[1024];
        scanf("%s", s);
        set<string> diff;
        queue<string> Q;
        string ret = "";
        diff.insert(s), Q.push(s);
        while (!Q.empty()) {
            string u = Q.front();
            Q.pop();
//            cout << u << endl;
            if (numicStringCompare(u, ret))
                continue;
            int r3 = 0, r7 = 0;
            int cond = 0;
            for (int i = 0; i < u.length(); i++) {
                r3 = (r3 * 10 + u[i] - '0')%3;
                r7 = (r7 * 10 + u[i] - '0')%7;
            }
            if(r3 == 0) {
                string v = divideString(u, 3);
                if (diff.find(v) == diff.end())
                    diff.insert(v), Q.push(v);
                cond = 1;
            }
            if (r7 == 0) {
                string v = divideString(u, 7);
                if (diff.find(v) == diff.end())
                    diff.insert(v), Q.push(v);
                cond = 1;
            }
            for (int i = 0; i < u.length(); i++) {
                if (u[i] == '3' || u[i] == '7') {
                    string v = removePos(u, i);
                    if (diff.find(v) == diff.end())
                        diff.insert(v), Q.push(v);
                    cond = 1;
                }
            }
            for (int i = 0; i < u.length(); i++) {
                int con3 = 0, con7 = 0;
                for (int j = i, k = 0; k < 3 && j < u.length(); j++, k++) {
                    if (u[j] == u[i])
                        con3++;
                    else    break;
                }
                for (int j = i, k = 0; k < 7 && j < u.length(); j++, k++) {
                    if (u[j] == u[i])
                        con7++;
                    else    break;
                }
                if (con3 == 3) {
                    string v = removePos(u, i, 3);
                    if (diff.find(v) == diff.end())
                        diff.insert(v), Q.push(v);
                    cond = 1;
                }
                if (con7 == 7) {
                    string v = removePos(u, i, 7);
                    if (diff.find(v) == diff.end())
                        diff.insert(v), Q.push(v);
                    cond = 1;
                }
            }
            if (cond == 0) {
                if (numicStringCompare(ret, u)) {
                    ret = u;
                }
            }
        }
        cout << ret << endl;
    }
    return 0;
}
/*
 3
 999
 273
 2331
 
 6
 4900006514979587103
 9305660497031957126752544737246
 13708976269278645181999140607
 1427490008594779
 107351103235212538538682
 65244379091939972650698
*/