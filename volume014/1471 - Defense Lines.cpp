#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 2*1e5+1;
int n,ans;
int a[maxn],g[maxn],f[maxn],bin[maxn];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int cas;
	cin >> cas;
	while (cas--){
		cin >> n;
		for (int i = 1; i <= n; ++i){
			cin >> a[i];
			if (a[i]>a[i - 1])
				g[i] = g[i - 1] + 1;
			else g[i] = 1;
		}
		a[n + 1] = 0;
		for (int i = n; i > 0; --i){
			if (a[i] < a[i + 1])
				f[i] = f[i + 1] + 1;
			else f[i] = 1;
		}

		ans = 0;
		memset(bin, 0x7f, sizeof(bin));
		bin[0] = -1;
		for (int i = 1; i <= n; ++i){
			ans = max(ans, int(f[i]+lower_bound(bin, bin+n, a[i])-bin-1));
			bin[g[i]] = min(bin[g[i]], a[i]);
		}

		cout << ans << '\n';
	}
	return 0;
}
