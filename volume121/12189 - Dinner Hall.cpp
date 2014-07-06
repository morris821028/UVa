// greedy 
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N;
	while(scanf("%d", &N) == 1 && N) {
		vector< pair<int, char> > R;
		int exit = 0, hh, mm, ss;
		char s[5];
		for(int i = 0; i < N; i++) {
			scanf("%d:%d:%d %s", &hh, &mm, &ss, s);
			R.push_back(make_pair(hh * 3600 + mm * 60 + ss, s[0]));
			if(s[0] == 'X')
				exit++;
		}
		sort(R.begin(), R.end());
		for(int i = N-1; i >= 0; i--) {
			if(R[i].second == '?') {
				if(exit < N/2)
					R[i].second = 'X', exit++;
				else
					R[i].second = 'E';
			}
		}
		
		int ret = 0, cnt = 0;
		for(int i = 0; i < N; i++) {
			if(R[i].second == 'E')
				cnt++;
			else
				cnt--;
			ret = max(ret, cnt);
		}
		printf("%d\n", ret);
	}
	return 0;
}
