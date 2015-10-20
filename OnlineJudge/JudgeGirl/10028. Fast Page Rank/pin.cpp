#include <bits/stdc++.h>
using namespace std;
double frandom() {
	return (double)(rand()%10) / 2;
}
double mrandom() {
	return (rand() * rand())%10;
}
int main() {
	freopen("4.in", "w", stdout);
    srand(time(NULL));
    int testcase = 1;
//    printf("%d\n", testcase);
    while (testcase--) {
    	int n = 3000;
    	printf("%d\n", n);
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++)
    			printf("%c", rand()%(n/20) == 0 ? '1' : '0');
    		puts("");
		}
	}
    return 0;
}
