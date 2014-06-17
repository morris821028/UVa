#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int main() {
    string word, origin;
    map<string, set<string> > o;
    while(cin >> word) {
        if(word == "XXXXXX") {
            break;
        }
        origin = word;
        sort(word.begin(), word.end());
        o[word].insert(origin);
    }
    while(cin >> word) {
        if(word == "XXXXXX") {
            break;
        }
        origin = word;
        sort(word.begin(), word.end());
        int flag = 0;
        for(set<string>::iterator it = o[word].begin(); it != o[word].end(); it++) {
            cout << *it << endl;
            flag = 1;
        }
        if(!flag)
            cout << "NOT A VALID WORD" << endl;
        cout << "******" << endl;
    }
    return 0;
}
