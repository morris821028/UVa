#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
int main() {
    string s, o;
    int cases = 0;
    while(1) {
        map<string, pair<int, pair<string, string> > > R;
        map<string, pair<int, pair<string, string> > >::iterator it;
        // ignore, count, first, last
        while(1) {
            if(getline(cin, s)) {
                if(s == "#")    break;
                stringstream sin(s);
                while(sin >> s) {
                    if(s.length() >= 5)
                        s = s.substr(0, 5);
                    o = s;
                    if(s.length() >= 3)
                        o[2] = '$';
                    if(R.find(o) == R.end())
                        R[o] = make_pair(1, make_pair(s, ""));
                    else {
                        it = R.find(o);
                        R[o] = make_pair((it->second).first+1, make_pair((it->second).second.first, s));
                    }
                }
            }
            else    return 0;
        }
        map<string, pair<int, string> > Ans;
        map<string, pair<int, string> >::iterator jt;
        for(it = R.begin(); it != R.end(); it++) {
            if((it->second.second).second != "")
                Ans[it->first] = make_pair((it->second).first, (it->second).second.second);
            else
                Ans[it->first] = make_pair((it->second).first, (it->second).second.first);
            //cout << (it->second).second.first << " " << (it->second).second.second << endl;
        }
        printf("Set #%d:\n", ++cases);
        for(jt = Ans.begin(); jt != Ans.end(); jt++) {
            if((jt->second).second != "")
                cout << (jt->second).second;
            else
                cout << jt->first;
            cout << " " << (jt->second).first << endl;
        }
        puts("");
    }
    return 0;
}
/*
xxab xxbb xxba xxaa
#
cd cde
#

Output:
Set #1:
xxaa 2
xxbb 2

Set #2:
cd 1
cde 1
//Wrong the problem description
//we should sort by xx-b and xx-a,
//and output the last ignored word.
*/
