#include <stdio.h> 
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int check(int mask, int val1, int val2) {
	int val = val2 - val1;
	if(val < 0)	return 0;
	if(val < 10) {
		if((mask>>val)&1)	return 1;
	} else {
		int d1 = val/10, d2 = val%10;
		if(d1 == d2)	
			return 0;
		if(((mask>>d1)&1) && ((mask>>d2)&1))	
			return 1;
	}
	return 0;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout);
	int n, A[10], cases = 0;
	while(scanf("%d", &n) == 1 && n) {
		map<int, int> R;
		for(int i = 0; i < n; i++)
			scanf("%d", &A[i]), R[A[i]] = i;
		
		int ret = (1<<10)-1, T = ret;
		for(int i = 0; i < (1<<10); i++) {
			int t = i;
			if(__builtin_popcount(i) > __builtin_popcount(ret) || 
				(__builtin_popcount(i) == __builtin_popcount(ret) && t >= T))
				continue;
			int ac[10] = {}, mm = 0;
			for(int j = 0; j < 10 && mm != R.size(); j++) {
				if(!((i>>j)&1))	continue;
				if(R.find(j) != R.end()) {
					int v = R[j];
					mm += ac[v] == 0, ac[v] = 1;
				}
				for(int k = 0; k < n && mm != R.size(); k++) {
					if(check(i^(1<<j), j, A[k])) {
						int v = R[A[k]];
						mm += ac[v] == 0, ac[v] = 1;
					}
				}
				for(int k = 0; k < 10 && mm != R.size(); k++)	{
					if(j == k)	continue;
					if(!((i>>k)&1))	continue;
					if(R.find(j * 10 + k) != R.end()) {
						int v = R[j * 10 + k];
						mm += ac[v] == 0, ac[v] = 1;
					}
					if(R.find(k * 10 + j) != R.end()) {	
						int v = R[k * 10 + j];
						mm += ac[v] == 0, ac[v] = 1;
					}
					for(int p = 0; p < n; p++) {
						if(check(i^(1<<j)^(1<<k), j * 10 + k, A[p])) {
							int v = R[A[p]];
							mm += ac[v] == 0, ac[v] = 1;
						}
						if(check(i^(1<<j)^(1<<k), k * 10 + j, A[p])) {
							int v = R[A[p]];
							mm += ac[v] == 0, ac[v] = 1;
						}
					}
				}
			}
			if(mm == R.size()) {
				ret = i, T = t;	
			}
		}				
		printf("Case %d: ", ++cases);
		for(int i = 9; i >= 0; i--) {
			if((ret>>i)&1)
				printf("%d", i);
		}
		puts("");

	}
	return 0;
}
