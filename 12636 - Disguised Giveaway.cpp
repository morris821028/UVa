#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);*/
    int testcase, cases = 0;
    long long MULT[40005];
    long double MM[40005];
    long long A[205];
    scanf("%d", &testcase);
    int i, j, k, l;
    while(testcase--) {
        int n, m;
        scanf("%d", &n);
        m = n*(n-1)/2;
        for(i = 0; i < m; i++)
            scanf("%lld", &MULT[i]);
        sort(MULT, MULT+m);
        for(i = 0; i < m; i++)
            MM[i] = (long double)MULT[i];
        long long a, b, c, tmp;
        int used[40005], output = 0;
        printf("Case %d: ", ++cases);
        for(i = 2; i < m; i++) {
            // A[0] * A[1] = MULT[0]
            // A[0] * A[2] = MULT[1]
            // A[1] * A[2] = MULT[i]
            a = (long long)round(sqrt((MM[0]*MM[1])/MM[i])+1.514e-5);
            b = (long long)round(sqrt((MM[0]*MM[i])/MM[1])+1.514e-5);
            c = (long long)round(sqrt((MM[i]*MM[1])/MM[0])+1.514e-5);
            if(a*b != MULT[0] || a*c != MULT[1] || b*c != MULT[i])
                continue;
            A[0] = a, A[1] = b, A[2] = c;
            memset(used, 0, sizeof(used));
            used[0] = 1, used[1] = 1, used[i] = 1;
            int idx = 2;
            for(j = 3; j < n; j++) {
                while(used[idx] == 1)   idx++;
                A[j] = MULT[idx] / A[0];
                int ok = 1;
                for(k = 0; k < j && ok; k++) {
                    tmp = A[j] * A[k];
                    for(l = idx; l < m; l++) {
                        if(used[l] == 0 && MULT[l] == tmp) {
                            used[l] = 1;
                            break;
                        }
                    }
                    if(l == m)// fail
                        ok = 0;
                }
                if(!ok) // fail
                    break;
            }
            if(j == n) {
                output = 1;
                printf("%lld", A[0]);
                for(j = 1; j < n; j++)
                    printf(" %lld", A[j]);
                puts("");
                break;
            }
        }
        if(i == m) {
            int v = 0;
            printf("%d\n", 5/v);
            puts("XXXXXXXXXXXXXXXX");
        }
    }
    return 0;
}
