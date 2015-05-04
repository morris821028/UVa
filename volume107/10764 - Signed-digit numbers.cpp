#include <stdio.h>
#include <iostream> 
#include <algorithm>
using namespace std;

long long bpow[16][35];
long long llabs(long long x) {
	return x < 0 ? -x : x;
}
string digit2str(int a) {
	if (a >= 0) {
		return string(1, a + '0');
	} else {
		return "'" + string(1, ((-a) + '0'));
	}
}
string exp_complement(string x) {
	string ret = "";
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == '\'') {
			ret += x[i+1], i++;
		} else {
			ret += '\'';
			ret += x[i];
		}
	}
	return ret;
}
string dfs(long long n, int blimit, int b, int a) {
	long long m = llabs(n);
	int bIdx = 0, aIdx = 0;
	for (bIdx = 0; bIdx < blimit; bIdx++)
		if (m <= a * bpow[b][bIdx])
			break;
			
	if (bIdx == blimit)
		return "N"; // NOT FOUND
	if (m <= a)
		return digit2str(n);
		
	for (aIdx = 0; aIdx <= a; aIdx++)
		if (m <= aIdx * bpow[b][bIdx])
			break;
	
	string ret = "";
	for (; aIdx >= -a; aIdx--) {
		string suffix = dfs(m - aIdx * bpow[b][bIdx], bIdx, b, a);
		if (suffix.length() > 0 && suffix[0] != 'N') { // FOUND
			int d = 0;
			for (int i = 0; i < suffix.length(); i++)
				d += isdigit(suffix[i]);
			ret = digit2str(aIdx) + string(bIdx - d, '0') + suffix;
			break; 
		}
	}
//	printf("%lld %s -- %d %d\n", m, ret.c_str(), bIdx, aIdx);
	if (n < 0)
		ret = exp_complement(ret);
	return ret; 
}
int main() {
	for (int i = 1; i < 16; i++) {
		bpow[i][0] = 1;
		for (int j = 1; j < 35; j++)
			bpow[i][j] = bpow[i][j-1] * i;
	}
	
	long long n, a, b;
	while (scanf("%lld %lld %lld", &n, &b, &a) == 3 && b) {
		string ret = dfs(n, 34, b, a);
		printf("%s\n", ret.c_str());
	}
	return 0;
}
