#include <stdio.h> 
#include <ctype.h>
#include <iostream>
using namespace std;

int getWeight(int v) {
	int w = 0;
	while(v) {
		if(v&1)		w += 500;
		else		w += 250;
		v = v>>1;
	}
	return w;
}
int main() {
	int testcase, cases = 0;
	char g[32][32];
	scanf("%d", &testcase);
	while(testcase--) {
		for(int i = 0; i < 8; i++)
			scanf("%s", g[i]);
		
		int lw = 0, rw = 0, lpos, rpos;
		string lc = "", rc = "";
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if(isupper(g[i][j]))
					lw += getWeight(g[i][j]), lc += g[i][j];
				if(g[i][j] == '_')
					lpos = i;
			}
		}
		for(int i = 0; i < 8; i++) {
			for(int j = 10; j < 18; j++) {
				if(isupper(g[i][j]))
					rw += getWeight(g[i][j]), rc += g[i][j];
				if(g[i][j] == '_')
					rpos = i;
			}
		}
		printf("Case %d:\n", ++cases);
		if((lw < rw) == (lpos < rpos) &&
			(lw == rw) == (lpos == rpos) &&
			(lw > rw) == (lpos > rpos))
			puts("The figure is correct.");
		else {
			for(int i = lc.length(); i < 6; i++)
				lc += '.';
			for(int i = rc.length(); i < 6; i++)
				rc += '.';
			if(lw == rw) {
				puts("........||........");
				puts(".../\\...||.../\\..."); 
				puts("../..\\..||../..\\..");
				puts("./....\\.||./....\\.");
				printf("/%s\\||/%s\\\n", lc.c_str(), rc.c_str());
				puts("\\______/||\\______/");
				puts("........||........");
			} else if(lw > rw) {
				puts("........||.../\\...");
				puts("........||../..\\..");
				puts(".../\\...||./....\\.");
				printf("../..\\..||/%s\\\n", rc.c_str());
				puts("./....\\.||\\______/");
				printf("/%s\\||........\n", lc.c_str());
				puts("\\______/||........");
			} else {
				puts(".../\\...||........");
				puts("../..\\..||........");
				puts("./....\\.||.../\\...");
				printf("/%s\\||../..\\..\n", lc.c_str());
				puts("\\______/||./....\\.");
				printf("........||/%s\\\n", rc.c_str());
				puts("........||\\______/");
			}
		}
	}
	return 0;
}
