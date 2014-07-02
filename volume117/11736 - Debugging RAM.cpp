#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

int main() {
	int b, v, q, bytes[256];
	char s[1024];
	
	while(scanf("%d %d", &b, &v) == 2) {
		map<string, int> R;
		unsigned long long val[256] = {};
		for(int i = 1; i <= v; i++) {
			scanf("%s %d", s, &bytes[i]);
			R[s] = i;
		}
		for(int i = 1; i <= v; i++) {
			string binary = "";
			for(int j = 0; j < bytes[i]; j++) {
				scanf("%s", s);
				binary += s;
			}
			for(int j = 0; j < binary.length(); j++)
				val[i] = (val[i]<<1) + binary[j] - '0';
		}
		scanf("%d", &q);
		while(q--) {
			scanf("%s", s);
			int x = R[s];
			printf("%s=", s);
			if(!x)	puts("");
			else	printf("%llu\n", val[x]);
		}
	}
	return 0;
}
