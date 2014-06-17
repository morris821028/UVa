/**********************************************************************************/
/*  Problem: a981 "求和問題" from                                             */
/*  Language: CPP (1426 Bytes)                                                    */
/*  Result: NA(score:80) judge by this@ZeroJudge                                  */
/*  Author: morris1028 at 2014-04-17 09:15:04                                     */
/**********************************************************************************/


#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main() {
	int n, m;
	int A[35];
	while(scanf("%d %d", &n, &m) == 2) {
		for(int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sort(A, A + n, greater<int>());
		int h1Cnt = n / 2, h2Cnt = n - h1Cnt;
		map<long long, vector<int> > h1, h2;
		for(int i = (1<<h1Cnt)-1; i >= 0; i--) {
			long long sum = 0;
			for(int j = 0; j < h1Cnt; j++) {
				if((i>>j)&1)	sum += A[j];
			}
			h1[sum].push_back(i);
		}
		for(int i = (1<<h2Cnt)-1; i >= 0; i--) {
			long long sum = 0;
			for(int j = 0; j < h2Cnt; j++) {
				if((i>>j)&1)	sum += A[j + h1Cnt];
			}
			h2[sum].push_back(i<<h1Cnt);
		}
		set<int> ret;
		for(map<long long, vector<int> >::iterator it = h1.begin();
			it != h1.end(); it++) {
			long long f = (long long)m - it->first;
			map<long long, vector<int> >::iterator jt = h2.find(f);
			if(jt != h2.end()) {
				for(vector<int>::iterator iv = it->second.begin();
					iv != it->second.end(); iv++) {
					for(vector<int>::iterator jv = jt->second.begin();
						jv != jt->second.end(); jv++) {
						ret.insert(*iv| *jv);
					}
				}
			}
		}
		if(ret.size() == 0)
			puts("-1");
		for(set<int>::reverse_iterator it = ret.rbegin();
			it != ret.rend(); it++) {
			for(int i = n-1; i >= 0; i--) {
				if(((*it)>>i)&1) {
					printf("%d ", A[i]);
				}
			}
			puts("");
		}
	}
	return 0;
}

