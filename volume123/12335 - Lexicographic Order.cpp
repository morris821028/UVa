#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int t, cases = 0, i, j;
    long long f[50] = {1};
    for(i = 1; i < 50; i++)
        f[i] = f[i-1] * i;
    scanf("%d", &t);
    while(t--) {
        char buf[50];
        long long n;
        scanf("%s %lld", buf, &n);
        printf("Case %d: ", ++cases);
        string s(buf);
        sort(s.begin(), s.end());
        int len = strlen(buf);
        int ans[50] = {}, used[50] = {};
        for(i = 0; i < len; i++) {
            int cnt = 0;
            while(n > f[len-i-1]) {
                n -= f[len-i-1];
                cnt++;
            }
            cnt++;
            for(j = 0; j < len; j++) {
                if(!used[j])    cnt--;
                if(cnt == 0) {
                    used[j] = 1;
                    ans[i] = s[j];
                    break;
                }
            }
        }
        for(i = 0; i < len; i++) {
            printf("%c", s[i]);
            for(j = 0; j < len; j++) {
                if(ans[j] == s[i]) {
                   // printf("%c", buf[j]);
                }
            }
        }
        puts("");
    }
    return 0;
}
