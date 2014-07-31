#include <stdio.h>
#include <string.h>
using namespace std;

int match[105][105], msize[105];
char seed[105], dictionary[105][105];
int dlen[105];
int mp[52];
int N, M, D;
int dfs(int idx) {
	if(idx == N) {
		int f = 1;
		for(int i = 1; i <= M; i++)
			f &= mp[i] != -1;
		return f;
	}
	for(int i = 0; i < D; i++) {
		if(dlen[i] != msize[idx])	continue;
		int ok = 1;
		for(int j = 0; j < msize[idx] && ok; j++) {
			if(mp[match[idx][j]] != -1 && mp[match[idx][j]] != dictionary[i][j])
				ok = 0;
		}
		if(ok) {
			int cp[52];
			for(int i = 1; i <= M; i++)	cp[i] = mp[i];
			for(int j = 0; j < msize[idx] && ok; j++)
				mp[match[idx][j]] = dictionary[i][j];
			if(dfs(idx+1))	return 1;
			for(int i = 1; i <= M; i++)	mp[i] = cp[i];
		}
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &M, &N);
		for(int i = 0; i < N; i++) {
			int j;
			for(j = 0; scanf("%d", &match[i][j]) && match[i][j]; j++);
			msize[i] = j;
		}
		scanf("%s", seed);
		memset(mp, -1, sizeof(mp));
		for(int i = 0; seed[i]; i++)
			mp[match[0][i]] = seed[i];
		for(D = 0; scanf("%s", &dictionary[D]) && dictionary[D][0] != '*'; D++) {
			dlen[D] = strlen(dictionary[D]);
		}
		dfs(0);
		for(int i = 1; i <= M; i++)		
			printf("%c", mp[i]);
		puts("");
	}
	return 0;
}
