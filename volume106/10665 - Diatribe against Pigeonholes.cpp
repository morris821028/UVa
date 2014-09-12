#include <stdio.h> 
#include <algorithm>
#include <vector>
using namespace std;

bool cmp1(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second || (a.second == b.second && a.first < b.first);
}
bool cmp2(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second || (a.second == b.second && a.first > b.first);
}
int main() {
	int testcase, N;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf ("%d %s", &N, s);
		pair<int, int> cnt[26] = {}, ret[26];
		for (int i = 0; i < N; i++)
			cnt[i].first = i + 'A';
		for (int i = 0; s[i] != '#'; i++) {
			if (s[i] >= 'A' && s[i] <= 'Z')
				cnt[s[i] - 'A'].second ++;
		}
		int l = 0, r = N - 1;
		for (int i = 0; i < N; ) {
			if (i+1 < N) {
				sort(cnt+i, cnt + N, cmp1);
				if (cnt[i].second != cnt[i+1].second) {
					if (cnt[i].first < cnt[i+1].first) {
						ret[l++] = cnt[i];
						sort(cnt+i+1, cnt + N, cmp2);
						ret[r--] = cnt[i+1];
					} else {
						swap(cnt[i], cnt[i+1]);
						ret[l++] = cnt[i];
						sort(cnt+i+1, cnt + N, cmp2);
						ret[r--] = cnt[i+1];
					}
				} else {
					sort(cnt+i, cnt + N, cmp1);
					ret[l++] = cnt[i];
					sort(cnt+i+1, cnt + N, cmp2);
					ret[r--] = cnt[i+1];
				}
				i += 2;
			} else {
				ret[l] = cnt[i];
				i++;
			}
		}
		for (int i = 0; i < N; i++)
		 	printf("%c%c", ret[i].first, i == N - 1 ? '\n' : ' ');
	 	for (int i = 0; i < N; i++)
		 	printf("%d%c", ret[i].second, i == N - 1 ? '\n' : ' ');
	}
	return 0;
}
