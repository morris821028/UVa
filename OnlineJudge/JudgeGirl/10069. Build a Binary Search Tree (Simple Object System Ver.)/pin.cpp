#include <bits/stdc++.h>
using namespace std;

// $ awk '{ sub("\r$", ""); print }' out.txt > output.txt
char randLetter() {
	if (rand()%2)
		return rand()%26 + 'a';
	return rand()%26 + 'A';
}
int main() {
	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 1;
    while (testcase--) {
    	int n = 30000;
    	printf("%d\n", n);
    	int A[30000];
    	for (int i = 0; i < n; i++)
    		A[i] = i;
    	for (int i = 0; i < 10; i++) {
    		int x = rand()%n;
    		int y = rand()%n;
    		swap(A[x], A[y]);
		}
		for (int i = 0; i < n; i++)
			printf("%d ", A[i]);
		puts("");
	}
    return 0;
}

