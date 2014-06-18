#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
    int m, cases = 0;
    char line[505];
    scanf("%d", &m);
    cin.ignore(100, '\n');
    while(m--) {
        gets(line);
        int ans = 0, i;
        int cnt[26] = {};
        for(i = 0; line[i]; i++) {
            if(line[i] >= 'a' && line[i] <= 'z')
                cnt[line[i]-'a']++;
            if(line[i] >= 'A' && line[i] <= 'Z')
                cnt[line[i]-'A']++;
        }
        sort(cnt, cnt+26);
        ans = 0;
        for(i = 0; i < 26; i++)
            ans += cnt[25-i]*(26-i);
        printf("Case #%d: %d\n", ++cases, ans);
    }
    return 0;
}
