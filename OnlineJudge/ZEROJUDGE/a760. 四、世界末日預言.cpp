#include <bits/stdc++.h>
using namespace std;
int isleap(int yy) {
	return (yy%4 == 0 && yy%100 != 0) || (yy%400 == 0) ;
}
int main() {
	string s;
	int b[32768];
	const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	long long mnday = LONG_LONG_MAX;
	while (getline(cin, s)) {
		int tmp[32768], bidx = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] >= 'A' && s[i] <= 'Z')
				tmp[bidx++] = s[i]%3;
			if (s[i] >= 'a' && s[i] <= 'z')
				tmp[bidx++] = s[i]%3;			
		}
		for (int shift = 0; shift+13 < bidx; shift++) {
			long long val = 0;
			for (int i = 0; i < 14; i++)
				val = val*10 + tmp[i+shift];
			int yy = tmp[shift]*1000 + tmp[shift+1]*100 + tmp[shift+2]*10 + tmp[shift+3];
			int mm = tmp[shift+4]*10 + tmp[shift+5];
			int dd = tmp[shift+6]*10 + tmp[shift+7];
			int hh = tmp[shift+8]*10 + tmp[shift+9];
			if (hh >= 24 || mm > 12 || dd > days[mm] + isleap(yy))
				continue;
			if (val > 20130918133000LL && val <= mnday) {
				mnday = val;
				for(int i = 0; i < 14; i++)
					b[i] = tmp[i+shift];
			}
		}
	}		
	printf("%d%d%d%d/%d%d/%d%d %d%d:%d%d:%d%d\n", b[0], b[1], b[2], b[3]
			, b[4], b[5], b[6], b[7]
			, b[8], b[9], b[10], b[11], b[12], b[13]);
	return 0;
}

