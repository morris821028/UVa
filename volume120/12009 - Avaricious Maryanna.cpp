#include <stdio.h> 
#include <algorithm>
#include <vector>
using namespace std;

int rval[2048][512], rvalIdx;
vector<int> ret[512];
void test(int idx, int n) {
	int v[1024] = {}, add[1024];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			v[i+j] += rval[idx][i] * rval[idx][j];
	}
	for(int i = 0; i <= 2*n; i++)
		v[i+1] += v[i]/10, v[i] %= 10;
	for(int i = 0; i <= 9; i++) {
		int t = (i * v[0] * 2 + v[n])%10;
		if(t == i) {
			rval[rvalIdx][n] = i;
			for(int j = n-1; j >= 0; j--)
				rval[rvalIdx][j] = rval[idx][j];
			ret[n+1].push_back(rvalIdx);
			rvalIdx++;
		}
	}
}
void build() {
	rval[0][0] = 0;
	rval[1][0] = 1;
	rval[2][0] = 5;
	rval[3][0] = 6;
	ret[1].push_back(0);
	ret[1].push_back(1);
	ret[1].push_back(2);
	ret[1].push_back(3);
	rvalIdx = 4;
	for(int i = 1; i < 500; i++) {
		for(int j = 0; j < ret[i].size(); j++) {
			test(ret[i][j], i);
		}
	}
}
int testcase, N, cases = 0;
bool cmp(int a, int b) {
	for(int i = N-1; i >= 0; i--)
		if(rval[a][i] != rval[b][i])
			return rval[a][i] < rval[b][i];
	return false;
}
int main() {
	build();
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout);
	
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		printf("Case #%d:", ++cases);
		vector<int> out;
		for(int i = 0; i < ret[N].size(); i++) {
			if(rval[ret[N][i]][N-1] == 0 && N != 1)
				continue;
			out.push_back(ret[N][i]);
		}
		sort(out.begin(), out.end(), cmp);
		for(int i = 0; i < out.size(); i++) {
			printf(" ");
			for(int j = N-1; j >= 0; j--)
				printf("%d", rval[out[i]][j]);
		}
		puts("");
	}
	return 0;
}
