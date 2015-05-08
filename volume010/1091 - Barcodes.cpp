#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map> 
#include <vector>
#include <algorithm>
using namespace std;

class Code11 {
public:
	map<string, int> code;
	Code11() {
		code["00001"] = 0, code["10001"] = 1;
    	code["01001"] = 2, code["11000"] = 3;
    	code["00101"] = 4, code["10100"] = 5;
    	code["01100"] = 6, code["00011"] = 7;
    	code["10010"] = 8, code["10000"] = 9;
    	code["00100"] = 10; // -
    	code["00110"] = -1;
	}
	string scan(int n, int b[]) { 
		if (n%6 != 5)		return "bad code";
		if ((n + 1)/6 < 5)	return "bad code";	// S?CKE
		int m = (n + 1)/6;
		int mxw, mnw;
		mxw = 0, mnw = 0x3f3f3f3f;
		for (int i = 0; i < n; i++)
			mxw = max(mxw, b[i]), mnw = min(mnw, b[i]);
		double t = (mnw + mxw) / 2.0;
		mxw = 0, mnw = 0x3f3f3f3f;
		for (int i = 0; i < n; i++) {
			int v = 0;
			if (b[i] < t)
				v = b[i] * 2;
			else
				v = b[i];
			mxw = max(mxw, v), mnw = min(mnw, v);
		}
		if (mxw * 95 > mnw * 105) 	// 5% larger or smaller than intended
			return "bad code";
		string bcode[256];
		for (int i = 0, j = 0; i < n; i += 6, j++) {
			bcode[j] = "";
			for (int k = i; k < i+5; k++) {
				if (b[k] < t)
					bcode[j] = bcode[j] + "0";
				else
					bcode[j] = bcode[j] + "1";
			}
			if (i+5 < n && b[i+5] >= t)	// separate bar = 0 
				return "bad code";
		}
		if (bcode[0] == "01100") {		// modify decode order to START-XXX-STOP
			reverse(bcode, bcode + m);
			for (int i = 0; i < m; i++)
				reverse(bcode[i].begin(), bcode[i].end());
		}
		if (bcode[0] != "00110" || bcode[m-1] != "00110")
			return "bad code";
		for (int i = 0; i < m; i++) { 	// undefine code
			if (!code.count(bcode[i]))
				return "bad code";
			if (i > 0 && i < m-1 && code[bcode[i]] == -1)
				return "bad code";
		}
		
		int C = 0, K = 0;
		for (int i = 1; i < m - 3; i++)
			C = (C + (((m - 4) - i)%10 + 1) * code[bcode[i]])%11;
		for (int i = 1; i < m - 2; i++)
			K = (K + (((m - 4) - i + 1)%9 + 1) * code[bcode[i]])%11;
		
		if (C != code[bcode[m - 3]])
			return "bad C";
		if (K != code[bcode[m - 2]])
			return "bad K";
		
		string res;
		for (int i = 1; i < m - 3; i++) {
			int v = code[bcode[i]];
			if (v < 10)	res += (char)(v + '0');
			else		res += (char)('-');
		}
		return res;
			
	} 
} g;
int main() {
	int n, b[256], cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &b[i]);
		string response = g.scan(n, b);
		printf("Case %d: %s\n", ++cases, response.c_str());
	}
	return 0;
}
