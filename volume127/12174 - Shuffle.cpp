#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 100005;
int ans, cas, s, n;
int x[3*maxn], idx[maxn<<1], cnt[maxn];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> cas;
    while (cas--){
        cin >> s >> n;
        memset(x, 0, sizeof(int)*(n+(s<<1)+1));
        memset(cnt, 0, sizeof(int)*(s+1));
        memset(idx, 0, sizeof(int)*(n+s+1));
        for (int i = 0; i < n; ++i) cin >> x[i+s];

        int tot = 0;
        for (int i = 0; i < n + s + 1; ++i){
            if ((tot == s) || (i < s && tot == i) || (i > n && tot == n + s - i)) 
                idx[i] = 1;

            if (x[i] && !--cnt[x[i]]) --tot;
            if (x[i + s] && !cnt[x[i + s]]++) ++tot;
        }
        
        ans = 0;
        for (int i = 0; i < s; ++i) {
            bool isOK = true;
            for (int j = i; j < n + s + 1; j += s) {
                if (!idx[j]){
                    isOK = false;
                    break;
                }
            }
            if (isOK) ++ans;
        }
        if (ans > n) ans = s;
        cout << ans << '\n';
    }
    return 0;
}
