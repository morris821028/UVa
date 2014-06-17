#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        while(getchar()!='\n');
        map<string, string> r;
        map<string, int> s;
        string a, b;
        while(n--) {
            getline(cin, a);
            getline(cin, b);
            r[a] = b;
        }
        scanf("%d", &n);
        while(getchar()!='\n');
        while(n--) {
            getline(cin, a);
            s[a]++;
        }
        int top = -1, tie = 0;
        string ans = "";
        for(map<string, string>::iterator it = r.begin(); it != r.end(); it++) {
            int cnt = s[it->first];
            if(cnt > top)
                top = cnt, tie = 0, ans = it->second;
            if(cnt == top)
                tie++;
        }
        if(tie != 1)
            ans = "tie";
        cout << ans << endl;
        if(t)
            puts("");
    }
    return 0;
}
