#include <stdio.h>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

int main() {
	char s[1024];
	vector<int> C;
	for(int i = 1; i <= 6; i++)
		for(int j = 1; j <= 6; j++)
			C.push_back(i + j);
	sort(C.begin(), C.end());
	gets(s);
	while(gets(s)) {
		int cnt[128] = {};
		vector<int> M;
		for(int i = 0; s[i]; i++)
			cnt[s[i]]++;
		for(int i = 'A'; i <= 'Z'; i++) {
			if(cnt[i])
				M.push_back(cnt[i]);				
		}
		for(int i = '0'; i <= '9'; i++) {
			if(cnt[i])
				M.push_back(cnt[i]);				
		}
		sort(M.begin(), M.end(), greater<int>());
		int ret = 0;
		for(int i = 0; i < M.size(); i++) {
			ret += M[i] * C[i];
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
CALL DEA
WALTER WHITE
09AZ
*/
