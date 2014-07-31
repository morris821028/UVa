#include <stdio.h> 
#include <stack>
#include <queue>
using namespace std;

long long gcd(long long x, long long y) {
	for(long long t; x%y; t = x, x = y, y = t%y);
	return y;
}
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		// simulation
		queue<int> Q;
		stack<int> minute, five, hour;
		for(int i = 0; i < n; i++)
			Q.push(i);
		for(int i = 0; i < 24 * 60; i++) {
			int x = Q.front();
			Q.pop();
			if(minute.size() < 4) {
				minute.push(x);
			} else {
				while(!minute.empty())
					Q.push(minute.top()), minute.pop();
				if(five.size() < 11)
					five.push(x);
				else {
					while(!five.empty())
						Q.push(five.top()), five.pop();
					if(hour.size() < 11)
						hour.push(x);
					else {
						while(!hour.empty())
							Q.push(hour.top()), hour.pop();
						Q.push(x);
					}
				}
			}
		}
		
		// permutation group
		int M[8192], visited[8192] = {};
		for(int i = 0; i < n; i++)
			M[i] = Q.front(), Q.pop();
		long long ret = 1;
		for(int i = 0; i < n; i++) {
			if(visited[i] == 0) {
				int j, len = 1;
				visited[i] = 1;
				for(j = M[i]; j != i; j = M[j]) {
					visited[j] = 1, len++;
				}
				ret = ret / gcd(ret, len) * len;
			}
		}
		printf("%d balls cycle after %lld days.\n", n, ret);  
	}
	return 0;
}
