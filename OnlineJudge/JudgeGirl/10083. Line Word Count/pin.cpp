#include <bits/stdc++.h>
#include <random>
using namespace std;
double frandom() {
	return (double)(rand()%10) / 2;
}
double mrandom() {
	return (rand() * rand())%10;
}
char letterrand() {
	if (rand()%10 == 0)
		return ' ';
	if (rand()%53 < 26)	return rand()%26 + 'A';
	if (rand()%53 < 52)	return rand()%26 + 'a';
	return ' ';
}
int main() {
	freopen("in2.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 1;
    while (testcase--) {
    	int n = 4092;
    	for (int i = 0; i < n; i++) {
    		int m = rand()%32*128;
    		if (rand()%514 == 0) {
    			m = 1<<16;
    			fprintf(stderr, "has\n");
    		}
    		for (int j = 0; j < m; j++) {
    			char c = letterrand();
    			putchar(c);
			}
    		putchar('\n');
		}
	}
    return 0;
}
