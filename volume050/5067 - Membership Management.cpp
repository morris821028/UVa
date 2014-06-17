#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
using namespace std;

int main() {
    int n, i, j;
    string line, head, son;
    while(scanf("%d", &n) == 1 && n) {
        map<string, set<string> > g;
        string first;
        getchar();
        for(i = 0; i < n; i++) {
            cin >> line;
            head = "";
            int len = line.length();
            for(j = 0; j < len; j++) {
                if(line[j] == ':')  break;
                head += line[j];
            }
            if(i == 0)  first = head;
            for(j++, son = ""; j < len; j++) {
                if(line[j] == ',' || line[j] == '.') {
                    if(son != "") {
                        g[head].insert(son);
                    }
                    son = "";
                } else {
                    son += line[j];
                }
            }
            g[head];
        }
        queue<string> QQ;
        set<string> SS;
        QQ.push(first);
        while(!QQ.empty()) {
            first = QQ.front();
            QQ.pop();
            set<string>::iterator it = g[first].begin(), jt = g[first].end();
            for(; it != jt; it++) {
                if(g.find(*it) == g.end()) {
                    SS.insert(*it);
                } else {
                    QQ.push(*it);
                }
            }
            g.erase(first);
        }
        printf("%d\n", SS.size());
    }
    return 0;
}
