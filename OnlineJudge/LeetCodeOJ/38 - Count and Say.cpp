#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
	string int2str(int x) {
  		string s;
  		stringstream sin(s);
  		sin << x;
  		return sin.str();
	}
    string countAndSay(int n) {
        n--;
        string f1 = "1", f2;
        for (int i = 0; i < n; i++) {
        	f2 = "";
        	for (int j = 0; j < f1.length(); ) {
        		int cnt = 0, s = j;
        		while (j < f1.length() && f1[j] == f1[s])
        			j++, cnt++;
        		f2 = f2 + int2str(cnt) + f1[s];
        	}
        	f1 = f2;
        }
        return f1;
    }
};

int main() {
	Solution s;
	s.countAndSay(1);
	s.countAndSay(2);
	s.countAndSay(3);
	s.countAndSay(4);
	return 0;
}

