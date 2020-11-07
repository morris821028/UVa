#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 505;
long long num[maxn], sum[maxn];
char idx[maxn],a[maxn];
long long leftt,rightt,mid;
int m,k,n;

inline bool binSearch(){
    long long val = 0; int cnt = 0;
    memset(idx, 0, sizeof(idx));
    for(int i = m; i >= 1; --i){
        if(val+num[i] <= mid && i >= k-cnt)
            val += num[i];
        else{
            cnt++;
            val = num[i];
            idx[i] = 1;
        }
    }
    if(cnt == k-1){
        memcpy(a, idx ,sizeof(idx));
        return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int cas;
    cin >> cas;
    while(cas--){
        rightt = leftt = 0;
        cin >> m >> k;
        for(int i = 1; i <= m; ++i){
            cin >> num[i];
            rightt += num[i];
            leftt = num[i]>leftt ? num[i]:leftt;
        }
        while(rightt >= leftt){
            mid = (leftt+rightt) >> 1;
            if(binSearch()) rightt = mid -1;
            else leftt = mid+1;
        }
        for(int i = 1; i < m; ++i){
            cout << num[i] << ' ';
            if (a[i] == 1) cout << '/' << ' ';
        }
        cout << num[m] << '\n';
    }
    return 0;
}
