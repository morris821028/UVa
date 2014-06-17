#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
double get_avg(int l, int r, int sum[]) {
    return (double)(sum[r]-sum[l])/(r-l);
}
int q[100005], sum[100005];
double maxAvgProblem(int n, int L, int sum[]) {
    double ans = (double)sum[n]/n;
    int front, rear, i, j;
    int retL = 0, retR = n;
    front = 0, rear = -1;
    for(i = L; i <= n; i++) {
        int tmp = i-L;
        while(front < rear && get_avg(q[rear], tmp, sum) <= get_avg(q[rear-1], q[rear], sum))
            rear--;
        q[++rear] = tmp;
        while(front < rear && get_avg(q[front], i, sum) <= get_avg(q[front+1], i, sum))
            front++;
        double tans = get_avg(q[front], i, sum);
        if(tans > ans)
            ans = tans, retL = q[front], retR = i;
        if(tans == ans && i - q[front] < retR - retL)
			retL = q[front], retR = i;
    }
    printf("%d %d\n", retL + 1, retR);
    return ans;
}
int main() {
	int testcase, n, L;
	int i, j, k;
	char s[100005];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &L);
		scanf("%s", s+1);
		for(i = 1, sum[0] = 0; i <= n; i++)
			sum[i] = sum[i-1] + (s[i] == '1');
		maxAvgProblem(n, L, sum);
	}
	return 0;
}
