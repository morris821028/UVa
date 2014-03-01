#include <cstdio>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {
    char key = getchar();
    cin.ignore(1024, '\n');
    string s;
    int idx = 0;
    map<string, set<int> > r;
    while(getline(cin, s)) {
        ++idx;
        int i, len = s.length();
        for(i = 0; i < len; i++) {
            if(!isalpha(s[i]))
                continue;
            int j(i);
            string t = "";
            while(j < len) {
                if(isalpha(s[j]))
                    t += s[j];
                else
                    break;
                j++;
            }
            i = j;
            if(t[0] == key) {
                r[t].insert(idx);
            }
        }
    }
    for(map<string, set<int> >::iterator i = r.begin(); i != r.end(); i++) {
        cout << i->first;
        for(set<int>::iterator j = i->second.begin(); j != i->second.end(); j++)
            cout << " " << *j;
        cout << endl;
    }
    return 0;
}
/*
T
CONSIDER SEVERAL LINES OF TEXT AND ONE CHARCTER CALLED KEY,
SPECIFIED ON A LINE PRECEDING THE TEXT. THE WORDS IN THE TEXT ARE
SEPARAED BY SINGLE SPACE. THERE ARE NO WORDS SPLITTED BETWEEN TWO
LINES.
WRITE A PROGRAM TO DISPLAY AN INDEX OF ALL WORDS WIHIN THE TEXT
STARTING WITH THE KEY. THE INDEX MUST BE ALPHABETICALLY SORTED. EACH
WORD IN THE INDEX MUST BE FOLLOWED BY THE LIST OF THE LINE NUMBERS IN
WHICH IT APPEARS.
*/
