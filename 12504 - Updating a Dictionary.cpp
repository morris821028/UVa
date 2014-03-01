#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    char OLD[300], NEW[300];
    while(t--) {
        scanf("%s %s", &OLD, &NEW);
        map<string, string> O, N;
        int i, idx;
        char key[300], val[300];
        for(i = 1; OLD[i]; i++) {
            idx = 0;
            while(OLD[i] != ':')
                key[idx++] = OLD[i++];
            key[idx] = '\0';
            idx = 0, i++;
            while(OLD[i] != ',' && OLD[i] != '}')
                val[idx++] = OLD[i++];
            val[idx] = '\0';
            O[key] = val;
        }
        for(i = 1; NEW[i]; i++) {
            idx = 0;
            while(NEW[i] != ':')
                key[idx++] = NEW[i++];
            key[idx] = '\0';
            idx = 0, i++;
            while(NEW[i] != ',' && NEW[i] != '}')
                val[idx++] = NEW[i++];
            val[idx] = '\0';
            N[key] = val;
        }
        int flag = 0, tot = 0;
        for(map<string, string>::iterator it = N.begin();
            it != N.end(); it++) {
            if(O.find(it->first) == O.end()) {
                if(!flag)
                    printf("+");
                else
                    printf(",");
                cout << it->first;
                flag = 1;
            }
        }
        if(flag)    puts("");
        tot += flag, flag = 0;
        for(map<string, string>::iterator it = O.begin();
            it != O.end(); it++) {
            if(N.find(it->first) == N.end()) {
                if(!flag)
                    printf("-");
                else
                    printf(",");
                cout << it->first;
                flag = 1;
            }
        }
        if(flag)    puts("");
        tot += flag, flag = 0;
        for(map<string, string>::iterator it = N.begin();
            it != N.end(); it++) {
            if(O.find(it->first) != O.end()) {
                if(it->second != O[it->first]) {
                    if(!flag)
                        printf("*");
                    else
                        printf(",");
                    cout << it->first;
                    flag = 1;
                }
            }
        }
        if(flag)    puts("");
        tot += flag, flag = 0;
        if(!tot)    puts("No changes");
        puts("");
    }
    return 0;
}
