#include <iostream>
using namespace std;
main() {
	int n;
    freopen("in.txt", "rt", stdin);  
    freopen("out3.txt", "w+t", stdout);
    clock_t st, ed;
    st = clock();
	while(scanf("%d", &n) == 1) {
		int i;
		char t[26]={};
		for(i = 0; i < n; i++)	t[i] = i+'A';
		do {
			/*for(i = 0; i < n; i++)
				printf("%c",t[i]);
			puts("");*/
		} while(next_permutation(t,t+n));
	}
    ed = clock();
    printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC);
	return 0;
}
