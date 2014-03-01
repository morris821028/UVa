#include <stdio.h>
#include <string.h>

double get_avg(int l, int r, int sum[]) {
    return (double)(sum[r]-sum[l])/(r-l);
}
int main() {
    int L, n;
    char s[150];
    int i, j, q[150];
    while(scanf("%d %s", &L, s+1) == 2) {
        int sum[150] = {};
        n = strlen(s+1);
        for(i = 1; s[i]; i++)
            sum[i] = sum[i-1] +
            (s[i] == 'C' || s[i] == 'c' || s[i] == 'G' || s[i] == 'g');
        double ans = (double)sum[n]/n;
        int front, rear;
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
                ans = tans;
        }
        printf("%.2lf\n", ans + 1e-6);
    }
    return 0;
}
