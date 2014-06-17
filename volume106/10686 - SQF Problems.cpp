#include <stdio.h>
#include <map>
#include <iostream>
#include <ctype.h>
using namespace std;

int main() {
    int t, n, i, j;
    string pro[30], word, line;
    int W[30], P[30];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        map<string, int> R[30];
        for(i = 0; i < n; i++) {
            cin >> pro[i] >> W[i] >> P[i];
            for(j = 0; j < W[i]; j++) {
                cin >> word;
                R[i][word] = 0;
            }
        }
        cin.ignore(256, '\n');
        while(getline(cin, line)) {
            int len = line.length();
            if(len == 0)    break;
            for(i = 0; i < len; i++) {
                if(isalpha(line[i])) {
                    char buf[100], idx = 0;
                    while(i < len && isalpha(line[i]))
                        buf[idx++] = line[i++];
                    buf[idx] = '\0';
                    for(j = 0; j < n; j++) {
                        if(R[j].find(buf) != R[j].end()) {
                            R[j][buf] = 1;
                        }
                    }
                }
            }
        }
        int first = 0;
        for(i = 0; i < n; i++) {
            int cnt = 0;
            for(map<string, int>::iterator it = R[i].begin();
                it != R[i].end(); it++) {
                cnt += it->second;
            }
            if(cnt >= P[i]) {
                first++;
                if(first != 1)  printf(",");
                cout << pro[i];
            }
        }
        if(!first)
            cout << "SQF Problem.";
        cout << endl;

    }
    return 0;
}
