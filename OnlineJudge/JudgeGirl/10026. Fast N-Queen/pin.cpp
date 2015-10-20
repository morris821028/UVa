#include <bits/stdc++.h>
using namespace std;
double frandom() {
	return (double)(rand()%10) / 2;
}
double mrandom() {
	return (rand() * rand())%10;
}
int main() {
	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 1;
//    printf("%d\n", testcase);
    while (testcase--) {
    	int n = 8, m;
    	printf("%d\n", n);
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++)	{
    			printf("%c", rand()%(10) == 0 ? '*' : '.');
			}
			puts("");
		}
	}
    return 0;
}
