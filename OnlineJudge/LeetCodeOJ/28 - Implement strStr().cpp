#include <stdio.h>
#include <string.h>
#include <iostream>
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
	int KMPMatching(const char *T, const char *P, int tlen, int plen) {
	    int matchCnt = 0;
	    for (int i = 0, j = -1; i < tlen; i++) {
	        while (j >= 0 && P[j+1] != T[i])
	            j = kmpTable[j];
	        if (P[j+1] == T[i])  j++;
	        if (j == plen-1) {
	            matchCnt++;
	            if(matchCnt == 1)
	                return i - plen + 1;
	        }
	    }
	    return -1;
	}
    int strStr(string haystack, string needle) {
    	if (needle.length() == 0)
    		return 0;
        KMPtable(needle.c_str(), needle.length());
        return KMPMatching(haystack.c_str(), needle.c_str(), haystack.length(), needle.length());
    }
};

int main() {
	Solution s;
	printf("%d\n", s.strStr("abcde", "f"));
	return 0;
}
