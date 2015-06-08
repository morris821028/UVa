#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int need[256] = {}, dn = 0;
        for (int i = 0; i < t.length(); i++)
        	need[t[i]]++;
        for (int i = 0; i < 256; i++)
        	dn += need[i] > 0;
        	
        int l = 0, r = 0, cnt[256] = {};
        int mn = 0x3f3f3f3f, sat = 0;
        int sl = -1, sr = -1;
        
        for (; r < s.length(); r++) {
        	cnt[s[r]]++;
        	if (cnt[s[r]] == need[s[r]])
        		sat++;
        	while (l < s.length() && cnt[s[l]] > need[s[l]])
        		cnt[s[l]]--, l++;
        	if (sat == dn) {
        		if (r - l < mn) {
        			mn = r - l;
        			sl = l, sr = r;
        		}
        	}
        }
        if (sl == -1)	return "";
        return s.substr(sl, sr-sl+1);
    }
};

int main() {
	Solution s;
	cout << s.minWindow("ADOBECODEBANC", "ABC") << endl;
	return 0;	
}
