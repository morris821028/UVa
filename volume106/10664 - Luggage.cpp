#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;
int main() {
	string line;
	int T;
	scanf("%d", &T);
	getchar();
	while(T--) {
		getline(cin, line);
		istringstream in(line);
		int A[30], n = 0, sum = 0;
		int i, j, DP[201] = {};
		while(in>>A[n])	
			sum += A[n], n++;
		DP[0] = 1;
		if(sum%2 == 0) {
			sum /= 2;
			for(i = 0; i < n; i++) { 
				for(j = sum; j >= A[i]; j--) {
					if(DP[j-A[i]]) {
						DP[j] = 1;
					}
				}	
			} 
		}
		if(DP[sum] == 1)	puts("YES");
		else			puts("NO");
	}
    return 0;
}
