#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
#define MAXN 32767
	int kmpTable[MAXN];
	void KMPtable(const char *P, int len) {
	    int i, j;
	    kmpTable[0] = -1, i = 1, j = -1;
	    while (i < len) {
	        while (j >= 0 && P[j+1] != P[i])
	            j = kmpTable[j];
	        if (P[j+1] == P[i])
	            j++;
	        kmpTable[i++] = j;
	    }
	}
	vector<int> KMPMatching(const char *T, const char *P, int tlen, int plen) {
	    int matchCnt = 0;
	    vector<int> ret;
	    for (int i = 0, j = -1; i < tlen; i++) {
	        while (j >= 0 && P[j+1] != T[i])
	            j = kmpTable[j];
	        if (P[j+1] == T[i])  j++;
	        if (j == plen-1) {
	            matchCnt++;
	            j = kmpTable[j];
	            ret.push_back(i - plen + 1);
	            if(matchCnt == 2)
	                return ret;
	        }
	    }
	    return ret;
	}
    int solve(string s) {
        KMPtable(s.c_str(), s.length());
        string ds = s + s;
        vector<int> v = KMPMatching(ds.c_str(), s.c_str(), ds.length(), s.length());
        return v[1] - v[0]; 
    }
} kmp;

int main() {
	int testcase;
	char s[32767];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		printf("%d\n", kmp.solve(s));
	}
	return 0;
}
/*
5
aaaa
abababab
cdabcdabcdab
qwertyuiopasdfg
abcabcabcabcxabcabcabcabx
*/
