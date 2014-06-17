#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
int main() {
    int testcase;
    string A, B;
    string ta[105], tb[105];
    scanf("%d", &testcase);
    while(getchar() != '\n');
    while(testcase--) {
        getline(cin, A);
        getline(cin, B);
        stringstream sina(A), sinb(B);
        int na = 0, nb = 0;
        while(sina >> ta[na])   na++;
        while(sinb >> tb[nb])   nb++;
        if(na != nb) {
            puts("-");
            continue;
        }
        map<string, string> ma, mb;
        int error = 0, i;
        int fa, fb;
        bool update = false;
        do {
            update = false;
            for(i = 0; i < na; i++) {
                fa = 0, fb = 0;
                if(ta[i][0] == '<' && ta[i][ta[i].length()-1] == '>') {
                    if(ma.find(ta[i]) != ma.end())
                        ta[i] = ma[ta[i]], update = true, fa = 1;
                    else    fa = 0;
                } else  fa = 1;
                if(tb[i][0] == '<' && tb[i][tb[i].length()-1] == '>') {
                    if(mb.find(tb[i]) != mb.end())
                        tb[i] = mb[tb[i]], update = true, fb = 1;
                    else    fb = 0;

                } else  fb = 1;
                if(fa == 0 && fb == 1)
                    ma[ta[i]] = tb[i], ta[i] = tb[i], fa = 1;
                if(fa == 1 && fb == 0)
                    mb[tb[i]] = ta[i], tb[i] = ta[i], fb = 1;
                if(fa == 1 && fb == 1) {
                    if(ta[i] != tb[i])
                        error = 1;
                }
            }
        } while(update && !error);
        for(i = 0; i < na; i++) {
            fa = 0, fb = 0;
            if(ta[i][0] == '<' && ta[i][ta[i].length()-1] == '>')
                fa = 0;
            else
                fa = 1;
            if(tb[i][0] == '<' && tb[i][tb[i].length()-1] == '>')
                fb = 0;
            else
                fb = 1;
            if(fa == 0)
                ta[i] = "foo";
            if(fb == 0)
                tb[i] = "foo";
        }
        if(error) {
            puts("-");
            continue;
        }
        for(i = 0; i < na; i++) {
            if(i)   cout << " ";
            cout << ta[i];
        }
        cout << endl;


    }
    return 0;
}
/*
3
how now brown <animal>
<foo> now <color> cow
who are you
<a> <b> <a>
<a> b
c <a>

Output
how now brown cow
-
c b
*/
