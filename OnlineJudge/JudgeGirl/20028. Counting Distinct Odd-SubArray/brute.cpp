#include <bits/stdc++.h>
using namespace std;

int main() {
    int s[32768];
    int n, k;
    while (scanf("%d %d", &n, &k) == 2) {
    	for (int i = 0; i < n; i++)
    		scanf("%d", &s[i]);
    	set<vector<int>> S;
    	for (int i = 0; i < n; i++) {
    		vector<int> A;
    		int sum = 0;
    		for (int j = i; j < n; j++) {
    			sum += s[j] % 2 == 1;
    			if (sum > k)
    				break;
    			A.push_back(s[j]);
    			S.insert(A);
			}
		}
		printf("%d\n", S.size());
    }
    return 0;
}
/*
4 1 
1 2 3 4

4 2
1 1 2 3 

8
8 
*/ 
