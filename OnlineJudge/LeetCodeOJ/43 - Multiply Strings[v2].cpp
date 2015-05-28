#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string multiply(string sa, string sb) {
        vector<int> ret(sa.length() + sb.length(), 0);
        for (int i = sa.length()-1, j = 0; i >= 0; i--, j++) {
        	int p = sa[i] - '0', q;
        	if (p == 0)	continue;
        	for (int x = sb.length()-1, y = 0; x >= 0; x--, y++) {
        		q = sb[x] - '0';
        		ret[j + y] += p * q;
        	}
        }
        	
        int n = ret.size();
        
        vector<char> buff(n, '0');
        
        for (int i = 0; i < n; i++) {
        	if (ret[i] >= 10)
        		ret[i+1] += ret[i]/10;
        	ret[i] %= 10;
        	buff[i] = (int) ret[i] + '0';
        }
        
        int m = n-1;
        while (m > 0 && buff[m] == '0')
        	m--;
        
        string sret(buff.begin(), buff.begin() + m + 1);
        reverse(sret.begin(), sret.end());
        
        return sret;
    }
};

int main() {
	Solution s;
	string c= s.multiply("123", "456");
	cout << c << endl; 
	return 0;
}
