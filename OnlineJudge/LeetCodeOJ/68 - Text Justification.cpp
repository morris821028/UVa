#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
    	vector<string> ret;
        for (int i = 0; i < words.size(); ) {
        	int len = 0, w = 0, l = i;
        	while (i < words.size() && len + words[i].length() + 1 <= maxWidth + 1)
        		len += words[i].length() + 1, i++, w++;
        		
        	len -= w;
        	string s;
        	if (w == 1)	w++;
        	int base = (maxWidth - len) / (w-1), v = -1;
        	if ((maxWidth - len) % (w-1))
        		v = (maxWidth - len) % (w-1);
        	if (i == words.size())
        		base = 1, v = -1;
        	for (int j = l, k = 0, sum = 0; j < i; j++, k++) {
        		s += words[j], sum += words[j].length();
        		if (sum < maxWidth) {
        			if (k < v)
        				s += string(base+1, ' '), sum += base+1;
        			else
        				s += string(base, ' '), sum += base;
        		}
        	}
        	if (maxWidth > s.length())
        		s = s + string(maxWidth - s.length(), ' ');
        	ret.push_back(s);
        }
        return ret;
    }
};
int main() {
	Solution s;
	string A[] = {"Here","is","an","example","of","text","justification."};
	vector<string> v(A, A+7);
	s.fullJustify(v, 15);
//	string A[] = {"What","must","be","shall","be."};
//	vector<string> v(A, A+5);
//	s.fullJustify(v, 12);
	return 0;	
}
