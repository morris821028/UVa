#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
#define MAXN 32767
	int kmpTable[MAXN];
	int matchIdx[MAXN];
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
	int KMPmatching(const char *T, const char *P, int tlen, int plen, int mark) {
	    int matchCnt = 0;
	    for (int i = 0, j = -1; i < tlen; i++) {
	        while (j >= 0 && P[j+1] != T[i])
	            j = kmpTable[j];
	        if (P[j+1] == T[i])  j++;
	        if (j == plen-1) {
	            matchCnt++;
	            matchIdx[i - plen + 1] = mark;
	        }
	    }
	    return matchCnt > 0 ? 1 : -1;
	}
    vector<int> findSubstring(string s, vector<string>& words) {
    	sort(words.begin(), words.end());
    	vector<int> freqs;
    	int n = 1, m = words.size();
    	freqs.push_back(1);
    	for (int i = 1; i < words.size(); i++) {
    		if (words[i] == words[n-1]) {
    			freqs[n-1]++;
    		} else {
    			words[n++] = words[i];
    			freqs.push_back(1);
    		}
    	}
    	words.resize(unique(words.begin(), words.end()) - words.begin());
    	
    	for (int i = 0; i < s.length(); i++)
    		matchIdx[i] = -1;
    	for (int i = 0; i < words.size(); i++) {
    		KMPtable(words[i].c_str(), words[i].length());
    		KMPmatching(s.c_str(), words[i].c_str(), s.length(), words[i].length(), i);
    	}
    	
    	vector<int> ret;
    	int M = words[0].length();
    	for (int i = 0; i < M && i < s.length(); i++) {
    		map<int, int> R;
    		int diff = 0, window = M * (m - 1);
    		for (int r = i, l = i; r < s.length(); r += M) {
    			if (matchIdx[r] != -1) {
    				int &v = R[matchIdx[r]];
    				v++;
    				if (v == freqs[matchIdx[r]])	diff++;
    			} 
    			if (l < r - window) {
    				if (matchIdx[l] != -1) {
	    				int &v = R[matchIdx[l]];
	    				v--;
	    				if (v == freqs[matchIdx[l]]-1)	diff--;
    				}
					l += M;
    			}
    			
    			if (diff == words.size())
    				ret.push_back(l);
    		}
    	}
    	
        return ret;
    }
};

int main() {
	Solution s;
	string ss[] = {"foo", "bar"};
//	string ss[] = {"a", "a"};
	vector<string> d(ss, ss+2);
	vector<int> ret = s.findSubstring("barfoothefoobarman", d);
//	vector<int> ret = s.findSubstring("aa", d);
	for (int i = 0; i < ret.size(); i++)
		printf("%d\n", ret[i]);
	return 0;
}
