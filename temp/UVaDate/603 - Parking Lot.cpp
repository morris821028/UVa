#include <stdio.h> 
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int E[128] = {};
int hasE() {
	for (int i = 1; i <= 20; i++) 
		if (E[i])
			return 1;
	return 0;
}
int main() {
	int testcase, x;
	char s[128];
	scanf("%d", &testcase);
	while (testcase--) {
		int fin[128] = {};
		vector<int> A, B;
	
		while (scanf("%d", &x) == 1 && x != 99)
			A.push_back(x), B.push_back(x);
			
		while(getchar() != '\n');
		while (gets(s) && s[0] != '\0') {
			sscanf(s, "%d", &x);
			E[x] = 1;
			
			for (int it = 0; it < 32 && hasE(); it++) {
				for (int i = 0; i < A.size(); i++) {
					if (fin[i])	continue;
					if (E[A[i]])
						E[A[i]] = 0, fin[i] = 1;
				}
				if (hasE()) {
					for (int i = 0; i < A.size(); i++) {
						if (fin[i])	continue;
						A[i]++;
						if (A[i] > 20)	A[i] = 1;
					}
				}
			}
			
			if (hasE()) {
				for (int i = 0; i < A.size(); i++)
					if (fin[i] == 0)
						A[i] = B[i];
			}
		}
				
		for (int i = 0; i < A.size(); i++) {
			if (fin[i]) {
				printf("Original position %d parked in %d\n", B[i], A[i]);
			} else {
				printf("Original position %d did not park\n", B[i]);
			}
		}
		
		if (testcase)
			puts("");
	}
	return 0;
}
