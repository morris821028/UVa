#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
map<string, vector<vector<string> > > grammar;
map<string, set<string> > firstSet;
//First(alpha = A beta) = First(A), if lambda !belong First(A)
//                        First(A)-{lambda} then union First(beta), if lambda belong First(A)
set<string> findFirstSet(vector<string> right) {
    set<string> ret, First;
    if(right.size() == 0)
        return ret;
    map<string, vector<vector<string> > >::iterator it;
    map<string, set<string> >::iterator jt;
    it = grammar.find(right[0]);
    // grammar process LL
    if(it != grammar.end()) {
        for(vector<vector<string> >::iterator kt = it->second.begin();
            kt != it->second.end(); kt++) {// try each rule by [symbol]->[???]
            // replace each one grammar by [symbol->???] + right[1...n]
            vector<string> next;
            for(vector<string>::iterator lt = (*kt).begin();
                lt != (*kt).end(); lt++) {// concatenation [???]
                if((*lt) != "lambda")
                    next.push_back(*lt);
            }
            for(int i = 1; i < right.size(); i++)// concatenation + right[1...n]
                next.push_back(right[i]);
            First = findFirstSet(next);
            // make union
            for(set<string>::iterator it = First.begin();
                it != First.end(); it++)
                ret.insert(*it);
        }
        return ret;
    }
    jt = firstSet.find(right[0]);
    // process first set [terminal]
    if(jt != firstSet.end()) {
        ret = jt->second; // all first set
        if(ret.find("lambda") != ret.end()) {// do -{lambda}
            ret.erase("lambda");
            right.erase(right.begin());// do find First(beta)
            First = findFirstSet(right);
             for(set<string>::iterator it = First.begin();
                it != First.end(); it++)
                ret.insert(*it); // union result
        }
    } else { // this is a terminal
        ret.insert(right[0]);
    }
    return ret;
}
int main() {
    char str[1024];
    //grammar
    while(gets(str)) {
        if(str[0] == '\0')  break;
        int len = strlen(str);
        string left = "";
        vector<string> right;
        for(int i = 1; i < len; i++) {
            char buf[1024];
            int bufIdx = 0;
            while(str[i] != ',' && str[i] != ']')
                buf[bufIdx++] = str[i++];
            buf[bufIdx] = '\0';
            if(left == "")
                left = buf;
            else {
                right.push_back(buf);
                //cout << left << "->" << right << endl;
            }
        }
        grammar[left].push_back(right);
    }
    //first set
    while(gets(str)) {
        if(str[0] == '\0')  break;
        int len = strlen(str);
        string left = "", right;
        for(int i = 0; i < len; i++) {
            char buf[1024];
            int bufIdx = 0;
            while(str[i] != ',' && str[i] != ']' && str[i] != ' ')
                buf[bufIdx++] = str[i++];
            buf[bufIdx] = '\0';
            if(left == "") {
                left = buf;
                i++;
            } else {
                right = buf;
                //cout << left << "->" << right << endl;
                firstSet[left].insert(right);
            }
        }
    }
    // production rule of S
    while(gets(str)) {
        int len = strlen(str);
        string left = "";
        vector<string> right;
        for(int i = 1; i < len; i++) {
            char buf[1024];
            int bufIdx = 0;
            while(str[i] != ',' && str[i] != ']')
                buf[bufIdx++] = str[i++];
            buf[bufIdx] = '\0';
            if(left == "")
                left = buf;
            else {
                //cout << left << "->" << buf << endl;
                right.push_back(buf);
            }
        }
        cout << left << "->";
        for(int i = 0; i < right.size(); i++)
            cout << right[i];
        cout << " [";
        set<string> predictSet;
        predictSet = findFirstSet(right);
        for(set<string>::iterator it = predictSet.begin();
            it != predictSet.end(); it++) {
            if(it != predictSet.begin())    putchar(',');
            cout << *it;
        }
        cout << "]" << endl;
    }
    return 0;
}
