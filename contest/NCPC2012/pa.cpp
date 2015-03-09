#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string txt, s;
    while(getline(cin, txt)) {
        getline(cin, s);
        int idx = 0, i, j, len = s.length();
        int x;
        for(i = 0; i < len; i++) {
            if(s[i] == '<') {
                if(s[i+1] == '<') {
                    i++;
                    if(idx) {
                        txt.erase(idx-1, 1);
                        idx--;
                    }
                } else {
                    i += 2;
                    string num = "";
                    while(s[i] != ']')
                        num += s[i], i++;
                    stringstream sin;
                    sin << num;
                    sin >> x;
                    idx -= x;
                }
            } else if(s[i] == '>') {
                i += 2;
                string num = "";
                while(s[i] != ']')
                    num += s[i], i++;
                stringstream sin;
                sin << num;
                sin >> x;
                idx += x;
            } else if(s[i] == '^') {
                i += 2;
                string ins = "";
                while(s[i] != ']')
                    ins += s[i], i++;
                txt.insert(idx, ins);
                idx += ins.length()-1;
            } else if(s[i] == '#') {
                i += 2;
                string rep = "";
                while(s[i] != ']')
                    rep += s[i], i++;
                for(j = 0; j < rep.length(); j++)
                    txt[idx] = rep[j], idx++;
                idx--;
            } else {
                i += 2;
                string num = "";
                while(s[i] != ']')
                    num += s[i], i++;
                stringstream sin;
                sin << num;
                sin >> x;
                txt.erase(idx, x);
            }
        }
        cout << txt << endl;
    }
    return 0;
}/*
AK47 is powerful
>[2]^[B]>[1]#[48]
Sam sings badly
>[4]<<>[1]#[u]>[3]^[ i]>[6]![2]
Apple is better than Samsung
>[3]<<<<<<^[hTC]>[1]![2]
*/
